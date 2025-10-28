#ifndef LETTERS_HPP
#define LETTERS_HPP

#include "raylib.h"
#include <string>
#include <vector>

class FallingLetter {
public:
    Texture2D texture;
    float speed;
    float Height;

    void Render() const;
    void Update();
    bool OffScreen() const;
    
    static void SpawnCustom(const Texture2D& tex, float speed, float startHeight);
    static void UpdateAll();
    static void RenderAll();

private:
    static std::vector<FallingLetter> letters;
};

#endif