#include "LoadTextures.hpp"
#include "raylib.h"
#include "Globals.hpp"
#include <vector>

std::vector<Texture2D> Textures;

Texture2D LoadTextureFromFile(const char* filename) {
    Texture2D texture = LoadTexture(filename);
    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    Textures.push_back(texture);
    return texture;
}

void UnloadAllTextures() {
    for (auto& texture : Textures) {
        UnloadTexture(texture);
    }
    Textures.clear();
}

void registerTexture(Texture2D texture) {
    Textures.push_back(texture);
}

void LoadAllSprites() {
    LoadTextureFromFile("Resources/X_white.png"); // 1
    LoadTextureFromFile("Resources/triangle_white.png"); // 2
    LoadTextureFromFile("Resources/square_white.png"); // 3
    LoadTextureFromFile("Resources/circle_white.png"); // 4
}
