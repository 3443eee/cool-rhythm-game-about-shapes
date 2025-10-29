#include "raylib.h"
#include "Globals.hpp"
#include "background.hpp"
#include "LoadTextures.hpp"
#include "Render.hpp"
#include "Letters.hpp"
#include <string>
#include "Player.hpp"
using std::string;



void RenderScene() {
    BeginDrawing();
    DrawBackground();
    DrawRectangle(0, 0, screen_width * barThickness, screen_height, {0, 0, 0, 100});
    DrawRectangle(screen_width * barThickness, screen_height - screen_width * barThickness, screen_width, screen_width * barThickness, {0, 0, 0, 100});
    //DrawRectangle(screen_width * 0.25, screen_height * 0.125, screen_width * 0.68, screen_height * 0.2, {0, 0, 0, 100});
    //DrawText("Up next:", static_cast<int>(screen_width * 0.26f), static_cast<int>(screen_height * 0.125f), 20, WHITE);
    DrawLine(0,screen_height - screen_width * barThickness, screen_width * barThickness, screen_height - screen_width * barThickness, WHITE);
    DrawLine(screen_width * barThickness, screen_height - screen_width * barThickness, screen_width * barThickness, screen_height, WHITE);
    FallingLetter::RenderAll();
    RenderLetter();
    DrawFPS(screen_width * barThickness * 1.05, 0);
    EndDrawing();
}