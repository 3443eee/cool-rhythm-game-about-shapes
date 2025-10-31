#include "Music.hpp"
#include "raylib.h"

static Music backgroundMusic;

void playBackgroundMusic(const char* filePath) {
    backgroundMusic = LoadMusicStream(filePath);
    PlayMusicStream(backgroundMusic);
}

void updateBackgroundMusic() {
    UpdateMusicStream(backgroundMusic);
}