#include <string>
#include "raylib.h"
#include "Globals.hpp"
#include "Letters.hpp"
#include "background.hpp"
#include "LoadTextures.hpp"
#include "Render.hpp"
#include "UpdateGame.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int screen_width = 800;
int screen_height = 450;
//int screen_width = GetMonitorWidth(0);
//int screen_height = GetMonitorHeight(0);
//int screen_width;
//int screen_height;
float barThickness = 0.11;
float letterScale = 4.0f;

int main() {
    InitWindow(screen_width, screen_height, "L");
    InitAudioDevice();
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    //SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED);
    //SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
    //screen_width = GetMonitorWidth(0);   // monitor resolution
    //screen_height = GetMonitorHeight(0);
    //letterScale = (screen_width / 800.0f) * 3.0f;
    InitBackground();
    LoadAllSprites();
    GuiLoadStyle("Resources/dark.rgs");
    //ToggleFullscreen();
    while (!WindowShouldClose()) {
        UpdateGame();
        if (GuiButton({350, 250, 100, 40}, "Click Me!")) {
            TraceLog(LOG_INFO, "Button pressed!");
        }
        RenderScene();
    }
    UnloadAllTextures();
    CloseAudioDevice();
    CloseWindow();
}
