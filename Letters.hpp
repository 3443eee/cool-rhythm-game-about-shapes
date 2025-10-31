#ifndef LETTERS_HPP
#define LETTERS_HPP

#include "raylib.h"
#include <string>
#include <vector>

class FallingLetter {
public:
    Texture2D texture;
    float Height;      // Y for vertical, X for horizontal
    float speed;
    bool vertical = false;
    bool horizontal = false;

    // NEW: horizontal movement direction
    float horizontalMultiplier = -1.0f; // default move left

    static std::vector<FallingLetter> letters;

    void Render() const;
    void Update();
    bool OffScreen() const;

    static void SpawnCustom(const Texture2D& tex, float startPos, int direction, float timeToReach = 2.0f);
    static void UpdateAll();
    static void RenderAll();
};

#endif