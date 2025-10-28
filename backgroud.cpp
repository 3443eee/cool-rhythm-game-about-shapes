#include "background.hpp"
#include "raylib.h"
#include "Globals.hpp"
#include "LoadTextures.hpp"

Color BG = {200, 0, 33, 255};
Texture2D tile;
float tileScale;
Rectangle source;
Rectangle dest;
void InitBackground() {
    tile = LoadTexture("Resources/tile.png");
    SetTextureWrap(tile, TEXTURE_WRAP_REPEAT);
    SetTextureFilter(tile, TEXTURE_FILTER_POINT);
    registerTexture(tile);
    
    tileScale = 2.0f;
    source = {
        0.0f, 0.0f,
        (float)GetScreenWidth() / tileScale,
        (float)GetScreenHeight() / tileScale
    };
    dest = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };
}

void DrawBackground() {
    ClearBackground(BG);
    DrawTexturePro(tile, source, dest, {0, 0}, 0.0f, WHITE);
};