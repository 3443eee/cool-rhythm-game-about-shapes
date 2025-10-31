#include "UpdateGame.hpp"
#include "Globals.hpp"
#include "Letters.hpp"
#include "raylib.h"
#include "Player.hpp"
#include "LoadTextures.hpp"
#include "ParseLevelFile.hpp"
#include "Music.hpp"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

using std::string;

void startGame(int levelID) {
    in_game = true;
    game_time = 0;
    currentLevel = levelID;
    ParseLevelFile();
    playBackgroundMusic(string("Resources/Music/" + std::to_string(currentLevel) + ".mp3").c_str());
}

static std::chrono::high_resolution_clock::time_point lastTime;

void UpdateGame() {
    if (!in_game) {
        if (IsKeyPressed(KEY_S)) {
            startGame(1);
            lastTime = std::chrono::high_resolution_clock::now(); // reset timer when game starts
        }
        return;
    }
    
    // Only count time while in-game
    auto now = std::chrono::high_resolution_clock::now();
    auto deltaMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();
    game_time += deltaMs;
    lastTime = now;

    if (game_time > 100 && in_game == true) ParseLevelFile();
    updateBackgroundMusic();
    
    // --- Handle input ---
    if (IsKeyDown(KEY_D)) currentLetter = "triangle";
    if (IsKeyDown(KEY_F)) currentLetter = "square";
    if (IsKeyDown(KEY_J)) currentLetter = "circle";
    if (IsKeyDown(KEY_K)) currentLetter = "X";
    if (IsKeyPressed(KEY_SPACE)) FallingLetter::SpawnCustom(Textures[1], 400, screen_width, 1);
    if (IsKeyPressed(KEY_UP)) FallingLetter::SpawnCustom(Textures[3], 400, -80, 0);

    FallingLetter::UpdateAll();
}
