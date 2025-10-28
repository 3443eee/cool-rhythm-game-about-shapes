#include "Player.hpp"
#include "raylib.h"
#include <string>
#include "Globals.hpp"
#include "LoadTextures.hpp"
string currentLetter = "-";

void RenderLetter() {
    Texture2D texture;
    if (currentLetter == "triangle") {
        texture = Textures[2];
    } else if (currentLetter == "square") {
        texture = Textures[3];
    } else if (currentLetter == "circle") {
        texture = Textures[4];
    } else if (currentLetter == "X") {
        texture = Textures[1];
    } else {
        return;
    }
    float scale = 4.0f;
    float drawX = (screen_width * 0.18f / 2.0f) - (texture.width * scale / 2.0f);

    DrawTextureEx(
        texture,
        {drawX, screen_height * 0.8f},
        0.0f,
        scale,
        WHITE
    );
}