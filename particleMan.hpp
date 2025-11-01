// particleMan.hpp
#pragma once
#include "raylib.h"
#include <vector>

// Particle structure
struct Particle {
    Vector2 position;
    Vector2 velocity;
    float size;
    float lifetime;
    Color color;
};

// Settings for customizable particle spawning
struct ParticleSettings {
    Vector2 velocityMin;      // min velocity per axis
    Vector2 velocityMax;      // max velocity per axis
    float sizeMin;
    float sizeMax;
    float lifetimeMin;
    float lifetimeMax;
    Color colorMin;           // min RGB for randomization
    Color colorMax;           // max RGB
};

// Particle manager class
class ParticleMan {
public:
    std::vector<Particle> particles;

    ParticleMan();
    void SpawnParticle(Vector2 position, const ParticleSettings* settings = nullptr);
    void SpawnCelebration(int count);
    void Update(float dt);
    void Draw();
    void Clear();

    static void UpdateAll(float dt);
    static void RenderAll();
    static void ClearAll();

private:
    static std::vector<ParticleMan*> allInstances;
    static void Register(ParticleMan* instance);
};
