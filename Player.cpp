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

    float drawX = (screen_width * barThickness / 2.0f) - (texture.width * letterScale / 2.0f);
    float drawY = screen_height - (screen_width / 2) * barThickness - (texture.height * letterScale / 2.0f);

    DrawTextureEx(
        texture,
        {drawX, drawY},
        0.0f,
        letterScale,
        WHITE
    );
}