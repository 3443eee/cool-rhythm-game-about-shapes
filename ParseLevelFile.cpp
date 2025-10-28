#include "raylib.h"
#include "ParseLevelFile.hpp"
#include "Letters.hpp"
#include "Globals.hpp"
#include "LoadTextures.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

using std::vector;
using std::string;

vector<string> lines;

vector<std::string> ReadAllLines(const std::string& filePath) {
    lines.clear();
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << "\n";
        return lines; // return empty
    }

    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
};

int extractTime(string line) {
    int time = 0;
    int end = line.find_first_of(',');
    if (end == std::string::npos) return time;
    std::string timeStr = line.substr(1, end);
    try {
        time = std::stoi(timeStr);
    } catch (const std::invalid_argument& e) {
        time = 0;
    }
    return time;
}

int currentLine = 2;

void ParseLevelFile() {
    if (lines.empty()) {
        ReadAllLines("Resources/Levels/" + std::to_string(currentLevel) + ".DAT");
        return;
    }

    if (currentLine >= lines.size()) return;
    string line = lines[currentLine];

    int spawnTime = extractTime(line);
    if (spawnTime == 0) return;
    if (game_time >= spawnTime) {
        if (line.find("TRI") != std::string::npos) {
            FallingLetter::SpawnCustom(Textures[2], 400, -80);
        } else if (line.find("SQR") != std::string::npos) {
            FallingLetter::SpawnCustom(Textures[3], 400, -80);
        } else if (line.find("CIR") != std::string::npos) {
            FallingLetter::SpawnCustom(Textures[4], 400, -80);
        } else if (line.find("X") != std::string::npos) {
            FallingLetter::SpawnCustom(Textures[1], 400, -80);
        }
        currentLine++;
    }
}