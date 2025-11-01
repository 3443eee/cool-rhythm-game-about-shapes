#include "raylib.h"
#include "Globals.hpp"
#include "background.hpp"
#include "LoadTextures.hpp"
#include "Render.hpp"
#include "Letters.hpp"
#include "particleMan.hpp"
#include <string>
#include "Player.hpp"
using std::string;

void RenderScene() {
    BeginDrawing();
    DrawBackground();

    // Main UI Bars
    DrawRectangle(0, 0, screen_width * barThickness, screen_height, {0, 0, 0, 100});
    DrawRectangle(screen_width * barThickness, screen_height - screen_width * barThickness, screen_width, screen_width * barThickness, {0, 0, 0, 100});

    float progressBarX = screen_width / 4;
    float progressBarY = screen_height * 0.01;
    float progressBarWidth = screen_width / 2;
    float progressBarHeight = screen_height * 0.02;

    DrawRectangle(progressBarX, progressBarY, progressBarWidth, progressBarHeight, {0, 0, 0, 100});

    // Filled part of the progress bar based on 'progress' (0..100)
    float filledWidth = (progress / 100.0f) * progressBarWidth;
    DrawRectangle(progressBarX, progressBarY, filledWidth, progressBarHeight, WHITE);

    // Optional: draw border
    DrawRectangleLines(progressBarX, progressBarY, progressBarWidth, progressBarHeight, WHITE);

    // Other UI
    DrawLine(0,screen_height - screen_width * barThickness, screen_width * barThickness, screen_height - screen_width * barThickness, WHITE);
    DrawLine(screen_width * barThickness, screen_height - screen_width * barThickness, screen_width * barThickness, screen_height, WHITE);
    DrawText(std::to_string(score).c_str(), screen_width * barThickness + 10, screen_height - screen_width * barThickness - 40, 40, WHITE);
    
    //Particle effects
    
    ParticleMan::RenderAll();
    //Show the letters
    FallingLetter::RenderAll();
    RenderLetter();

    DrawFPS(screen_width * barThickness * 1.05, 0);

    EndDrawing();
}