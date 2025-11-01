#include "Letters.hpp"
#include "raylib.h"
#include "Globals.hpp"
#include "Player.hpp"
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
    float frameDistance = speed * GetFrameTime(); // distance moved this frame

    if (vertical) {
        Height += frameDistance;

        float scissorBottom = static_cast<float>(screen_height - screen_width * barThickness);
        float letterTop     = Height - texture.height; // top edge of the letter
        float letterBottom  = Height;                   // bottom edge

        // How much of the letter is below the scissor line (hidden)
        float hiddenPixels = std::clamp(letterBottom - scissorBottom, 0.0f, (float)texture.height);
        percentageHidden   = (hiddenPixels / (float)texture.height) * 100.0f;

    } else if (horizontal) {
        Height += frameDistance * horizontalMultiplier;

        float scissorLeft  = static_cast<float>(screen_width * barThickness);
        float scissorRight = static_cast<float>(screen_width - screen_width * barThickness);

        float letterLeft  = Height;
        float letterRight = Height + texture.width;

        float hiddenPixels = 0.0f;

        if (horizontalMultiplier < 0) {
            // moving left — hidden by left side
            hiddenPixels = std::clamp(scissorLeft - letterLeft, 0.0f, (float)texture.width);
        } else {
            // moving right — hidden by right side
            hiddenPixels = std::clamp(letterRight - scissorRight, 0.0f, (float)texture.width);
        }

        percentageHidden = (hiddenPixels / (float)texture.width) * 100.0f;
    }

    // Give score proportional to newly hidden percentage
    if (letterType == currentLetter && percentageHidden > lastScorePercentage) {
        score += static_cast<int>(percentageHidden - lastScorePercentage);
        lastScorePercentage = percentageHidden;
    }

    // Reset score tracking once fully hidden or offscreen
    if (percentageHidden >= 100.0f || OffScreen()) {
        lastScorePercentage = 0.0f;
        percentageHidden = 100.0f;
    }
}




bool FallingLetter::OffScreen() const {
    if (vertical) {
        return Height > screen_height;
    } else {
        return Height < 0;
    }
}

void FallingLetter::SpawnCustom(const Texture2D& tex, float startPos, int direction, float timeToReach) {
    FallingLetter newSprite;
    newSprite.texture = tex;
    newSprite.vertical = (direction == 0);
    newSprite.horizontal = (direction == 1);
    newSprite.Height = startPos;

    if (Textures.empty()) return;
    if (tex.id == Textures[0].id) return;
    if (tex.id == Textures[1].id) newSprite.letterType = "X";
    else if (tex.id == Textures[2].id) newSprite.letterType = "triangle";
    else if (tex.id == Textures[3].id) newSprite.letterType = "square";
    else if (tex.id == Textures[4].id) newSprite.letterType = "circle";
    else newSprite.letterType = "unknown";
    
    float distance = 0.0f;

    if (direction == 0) { // vertical
        distance = (float)screen_height - startPos;
        newSprite.speed = distance / timeToReach;
    } else { // horizontal
        if (startPos < 0) {
            distance = screen_width - startPos;
            newSprite.horizontalMultiplier = 1.0f;
        } else {
            distance = startPos;
            newSprite.horizontalMultiplier = -1.0f;
        }
        newSprite.speed = distance / timeToReach;
    }

    letters.push_back(newSprite);
}

void FallingLetter::UpdateAll() {
    for (auto &l : letters)
        l.Update();

    // Remove letters that are fully offscreen
    letters.erase(std::remove_if(letters.begin(), letters.end(),
                                 [](const FallingLetter &l){ 
                                     return l.OffScreen(); // offscreen letters are gone
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

