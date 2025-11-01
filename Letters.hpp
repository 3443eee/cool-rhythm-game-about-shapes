#ifndef LETTERS_HPP
#define LETTERS_HPP

#include "raylib.h"
#include <string>
#include <vector>

class FallingLetter {
public:
    Texture2D texture;
    float Height; 
    float speed;
    bool vertical = false;
    bool horizontal = false;
    float percentageHidden = 0.0f;
    float lastScorePercentage = 0.0f;
    std::string letterType;
    float horizontalMultiplier = -1.0f; // default move left (1.0f to move right)

    static std::vector<FallingLetter> letters;

    void Render() const;
    void Update();
    bool OffScreen() const;

    static void SpawnCustom(const Texture2D& tex, float startPos, int direction, float timeToReach = 2.0f);
    static void UpdateAll();
    static void RenderAll();
};

#endif