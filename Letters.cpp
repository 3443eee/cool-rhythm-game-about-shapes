#include "Letters.hpp"
#include "raylib.h"
#include "Globals.hpp"
#include <algorithm>
#include <cstdlib>
#include "LoadTextures.hpp"

std::vector<FallingLetter> FallingLetter::letters;

void FallingLetter::Render() const {
    float scale = 4.0f;  // or whatever scale you want

    // center the texture horizontally in the column
    float drawX = (screen_width * 0.18f / 2.0f) - (texture.width * scale / 2.0f);

    DrawTextureEx(
        texture,
        { drawX, Height },
        0.0f,   // rotation
        scale,
        WHITE
    );
}

void FallingLetter::Update() {
    Height += speed * GetFrameTime();
}

bool FallingLetter::OffScreen() const {
    return Height > screen_height;
}

void FallingLetter::SpawnCustom(const Texture2D& tex, float speed, float startHeight) {
    FallingLetter newSprite;
    newSprite.texture = tex;
    newSprite.Height = startHeight;
    newSprite.speed = speed;
    letters.push_back(newSprite);
}

void FallingLetter::UpdateAll() {
    for (auto &l : letters)
        l.Update();

    letters.erase(std::remove_if(letters.begin(), letters.end(),
                                 [](const FallingLetter &l){ 
                                     return l.OffScreen();
                                 }),
                  letters.end());
}

void FallingLetter::RenderAll() {
    int wallY = static_cast<int>(screen_height * 0.75f);
    BeginScissorMode(0, 0, static_cast<int>(screen_width * 0.18f), wallY);

    for (auto &l : letters)
        l.Render();

    EndScissorMode();
}
