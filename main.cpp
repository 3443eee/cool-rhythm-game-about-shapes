#include <string>
#include "raylib.h"
#include "Globals.hpp"
#include "Letters.hpp"
#include "background.hpp"
#include "LoadTextures.hpp"
#include "Render.hpp"
#include "UpdateGame.hpp"

int screen_width = 800;
int screen_height = 450;
bool in_game = false;
int currentLevel = 0;
int game_time = 0;

int main() {
    InitWindow(screen_width, screen_height, "cool rhythm game about shapes");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    InitBackground();
    LoadAllSprites();
    while (!WindowShouldClose()) {
        UpdateGame();
        RenderScene();
    }
    UnloadAllTextures();
    CloseWindow();
}