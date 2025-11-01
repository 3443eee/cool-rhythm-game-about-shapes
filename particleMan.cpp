#include "particleMan.hpp"
#include <cstdlib>
#include <iostream>
// Static member initialization
std::vector<ParticleMan*> ParticleMan::allInstances;

ParticleMan::ParticleMan() {
    Register(this); // automatically adds to allInstances
}

void ParticleMan::Register(ParticleMan* instance) {
    allInstances.push_back(instance);
}

void ParticleMan::SpawnParticle(Vector2 position, const ParticleSettings* settings) {
    Particle p;
    p.position = position;

    if (settings) {
        // Random velocity
        p.velocity.x = GetRandomValue((int)(settings->velocityMin.x*100), (int)(settings->velocityMax.x*100)) / 100.0f;
        p.velocity.y = GetRandomValue((int)(settings->velocityMin.y*100), (int)(settings->velocityMax.y*100)) / 100.0f;

        // Random size
        p.size = (float)GetRandomValue((int)settings->sizeMin, (int)settings->sizeMax);

        // Random lifetime
        p.lifetime = (float)GetRandomValue((int)(settings->lifetimeMin*100), (int)(settings->lifetimeMax*100)) / 100.0f;

        // Random color
        int r = GetRandomValue(settings->colorMin.r, settings->colorMax.r);
        int g = GetRandomValue(settings->colorMin.g, settings->colorMax.g);
        int b = GetRandomValue(settings->colorMin.b, settings->colorMax.b);
        p.color = (Color){ (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
    } else {
        // Default behavior
        p.velocity = {(float)GetRandomValue(-50, 50)/50.0f, (float)GetRandomValue(50,150)/50.0f};
        p.size = GetRandomValue(4, 8);
        p.lifetime = GetRandomValue(60, 120)/100.0f;
        int r = GetRandomValue(200, 255);
        int g = GetRandomValue(100, 255);
        int b = GetRandomValue(50, 200);
        p.color = (Color){ (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
    }

    particles.push_back(p);
}

void ParticleMan::Update(float dt) {
    for (int i = 0; i < (int)particles.size(); i++) {
        particles[i].position.x += particles[i].velocity.x * dt * 60; // multiply by 60 for visible movement
        particles[i].position.y += particles[i].velocity.y * dt * 60;
        std::cout << "Particle " << i << " at " << particles[i].position.x << ", " << particles[i].position.y << "\n";
        particles[i].lifetime -= dt;
        if (particles[i].lifetime <= 0) {
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}

void ParticleMan::Draw() {
    for (Particle &p : particles) {
        DrawRectangleV(p.position, {p.size, p.size}, p.color);
    }
}

void ParticleMan::Clear() {
    particles.clear();
}

// --------- Static global management ---------
void ParticleMan::UpdateAll(float dt) {
    for (ParticleMan* pm : allInstances) {
        pm->Update(dt);
    }
}

void ParticleMan::RenderAll() {
    for (ParticleMan* pm : allInstances) {
        pm->Draw();
    }
}

void ParticleMan::ClearAll() {
    for (ParticleMan* pm : allInstances) {
        pm->Clear();
    }
    allInstances.clear();
}

void ParticleMan::SpawnCelebration(int count) {
    // Example default settings for confetti/flames
    ParticleSettings settings;
    settings.velocityMin = {-2.0f, 2.0f};
    settings.velocityMax = {2.0f, 6.0f};
    settings.sizeMin = 8;
    settings.sizeMax = 16;
    settings.lifetimeMin = 0.8f;
    settings.lifetimeMax = 1.2f;
    settings.colorMin = {200,100,50,255};
    settings.colorMax = {255,255,200,255};

    for (int i = 0; i < count; i++) {
        // Spawn at random horizontal position along top
        SpawnParticle({ (float)GetRandomValue(0, GetScreenWidth()), 0.0f }, &settings);
    }
}