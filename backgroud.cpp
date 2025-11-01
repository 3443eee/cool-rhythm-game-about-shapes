#include "background.hpp"
#include "raylib.h"
#include "Globals.hpp"
#include "LoadTextures.hpp"

Color BG = {200, 0, 33, 255};
Texture2D tile;
float tileScale;
Rectangle source;
Rectangle dest;

bool fading = false;
float fadingTicks = 0;
float startTick = 0;
int fadeTime = 0;
Color targetColor;
Color startColor;

Color brighten(Color c, float factor = 1.2f) {
    // Multiply RGB channels by factor, clamp to 255
    return Color{
        (unsigned char)std::min(int(c.r * factor), 255),
        (unsigned char)std::min(int(c.g * factor), 255),
        (unsigned char)std::min(int(c.b * factor), 255),
        c.a
    };
}

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
    if (fading) {
        fadingTicks += GetFrameTime() * 1000.0f;
        float progress = fadingTicks / fadeTime;
        if (progress >= 1.0f) {
            BG = targetColor;
            fading = false;
            fadingTicks = 0;
        } else {
            BG.r = (unsigned char)(startColor.r + (targetColor.r - startColor.r) * progress);
            BG.g = (unsigned char)(startColor.g + (targetColor.g - startColor.g) * progress);
            BG.b = (unsigned char)(startColor.b + (targetColor.b - startColor.b) * progress);
        }
    }
    DrawTexturePro(tile, source, dest, {0, 0}, 0.0f, WHITE);
}


void SetBackgroundColor(Color color, int ft) {
    fadeTime = ft;
    targetColor = color;
    startColor = BG; // save the color at fade start
    fading = true;
    fadingTicks = 0;
}
