#include "Letters.hpp"
#include "raylib.h"
#include "Globals.hpp"
#include <algorithm>
#include <cstdlib>
#include "LoadTextures.hpp"

std::vector<FallingLetter> FallingLetter::letters;

void FallingLetter::Render() const {
    // center the texture horizontally in the column
    if (vertical) {
        float drawX = (screen_width * barThickness / 2.0f) - (texture.width * letterScale / 2.0f);
        DrawTextureEx(
            texture,
            { drawX, Height },
            0.0f,   // rotation never gonna be using rotation i think, but raylib wants it, but i might, so leaving it here, but who knows, i might use it?? nah ill never use it..... OR.... MAYBE I WILL
            letterScale,
            WHITE
        );
    } else {
        float drawY = (screen_height - (screen_width / 2) * barThickness) - ( texture.height * letterScale / 2.0f );

        DrawTextureEx(
            texture,
            { Height, drawY },
            0.0f,
            letterScale,
            WHITE
        );
    } 
}

void FallingLetter::Update() {
    if (vertical)
        Height += speed * GetFrameTime();
    else if (horizontal) {
        Height -= speed * GetFrameTime();
    }
}

bool FallingLetter::OffScreen() const {
    if (vertical) {
        return Height > screen_height;
    } else {
        return Height > screen_width;
    }
}

void FallingLetter::SpawnCustom(const Texture2D& tex, float speed, float startHeight, int direction) {
    if (direction == 0) { // vertical
        FallingLetter newSprite;
        newSprite.texture = tex;
        newSprite.Height = startHeight;
        newSprite.speed = speed;
        newSprite.vertical = true;
        newSprite.horizontal = false;
        letters.push_back(newSprite);
        return;
    } else if (direction == 1) { // horizontal
        FallingLetter newSprite;
        newSprite.texture = tex;
        newSprite.Height = startHeight;
        newSprite.speed = speed;
        newSprite.vertical = false;
        newSprite.horizontal = true;
        letters.push_back(newSprite);
        return;
    }
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
    for (auto &l : letters) {
        if (l.vertical) {
            int wallY = static_cast<int>(screen_height - screen_width * barThickness);
            BeginScissorMode(0, 0, static_cast<int>(screen_width * barThickness), wallY);
        } else if (l.horizontal) {
            int wallX = static_cast<int>(screen_width * barThickness);
            BeginScissorMode(wallX, screen_height - wallX, screen_width - wallX, wallX);
        }
        l.Render();
        EndScissorMode();
    }
}

