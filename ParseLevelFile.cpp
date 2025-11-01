#include "raylib.h"
#include "ParseLevelFile.hpp"
#include "particleMan.hpp"
#include "Letters.hpp"
#include "Globals.hpp"
#include "LoadTextures.hpp"
#include "background.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

using std::string;
using std::vector;

static vector<string> lines;
static int currentLine = 0;
ParticleMan confetti;

// Reads all lines into memory
vector<string> ReadAllLines(const string& filePath) {
    lines.clear();
    std::ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << "\n";
        return lines;
    }

    while (std::getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }
    file.close();
    return lines;
}

// Parse "time" (the first number before the first comma)
int extractTime(const string& line) {
    size_t commaPos = line.find(',');
    if (commaPos == string::npos) return -1;
    try {
        return std::stoi(line.substr(0, commaPos));
    } catch (...) {
        return -1;
    }
}

// Parse color line: "0, COL, r,g,b"
Color extractColor(const string& line) {
    std::stringstream ss(line);
    string part;
    int time, r, g, b;
    std::getline(ss, part, ','); // time
    std::getline(ss, part, ','); // " COL"
    std::getline(ss, part, ','); r = std::stoi(part);
    std::getline(ss, part, ','); g = std::stoi(part);
    std::getline(ss, part, ','); b = std::stoi(part);
    return (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, 255};
}

int extractColorParameter (const string& line, int index) {
    std::stringstream ss(line);
    string part;
    int fadeTime = 0;
    std::getline(ss, part, ','); // time
    std::getline(ss, part, ','); // " COL"
    std::getline(ss, part, ','); // r
    std::getline(ss, part, ','); // g
    std::getline(ss, part, ','); // b
    std::getline(ss, part, ','); // b
    std::getline(ss, part, ','); fadeTime = std::stoi(part); // fadeTime
    return fadeTime;
}

int GetLevelLength(const std::vector<std::string>& lines) {
    int maxTime = 0;

    for (const auto& line : lines) {
        int spawnTime = extractTime(line);
        if (spawnTime == -1) continue;

        int duration = 0;

        int lineEnd = spawnTime + duration;
        if (lineEnd > maxTime) maxTime = lineEnd;
    }

    return maxTime;
}

// Main parser logic
void ParseLevelFile() {
    if (lines.empty()) {
        ReadAllLines("Resources/Levels/" + std::to_string(currentLevel) + ".DAT");
        currentLine = 0;
        return;
    }

    if (currentLevelLenght == 0) {
        currentLevelLenght = GetLevelLength(lines);
    }
    
    if (currentLine >= (int)lines.size()) return;

    string line = lines[currentLine];
    int spawnTime = extractTime(line);
    if (spawnTime == -1) { currentLine++; return; }

    const float timeToReach = 1.0f;

    if (game_time >= spawnTime) {
        if (line.find("COL") != string::npos) {
            Color color = extractColor(line);
            std::cout << "Color changed to: "
                    << (int)color.r << ", "
                    << (int)color.g << ", "
                    << (int)color.b << "\n";
            int fadeTime = extractColorParameter(line, 5);
            if (fadeTime <= 0) fadeTime = 1000; // default fade time
            SetBackgroundColor(color, fadeTime);
            std::cout << " with fade time: " << fadeTime << "ms\n";
        } else if (line.find("PAR") != string::npos) {
            std::cout << "Celebration triggered at time: " << spawnTime << "ms\n";
            confetti.SpawnCelebration(50);
        } else {
            Texture2D tex;
            int verticalDirection = 0; // top-to-bottom
            int horizontalDirection = 1; // right-to-left

            // Determine texture
            if (line.find("TRI") != string::npos) tex = Textures[2];
            else if (line.find("SQR") != string::npos) tex = Textures[3];
            else if (line.find("CIR") != string::npos) tex = Textures[4];
            else if (line.find("X")   != string::npos) tex = Textures[1];
            else tex = Textures[0]; // fallback, if needed

            // Determine direction and starting position
            if (line.find("BOT") != string::npos) {
                // Horizontal from right side
                FallingLetter::SpawnCustom(tex, screen_width, horizontalDirection, timeToReach);
            } else {
                // Vertical from top
                FallingLetter::SpawnCustom(tex, -80.0f, verticalDirection, timeToReach);
            }
        }

        currentLine++;
    }
}