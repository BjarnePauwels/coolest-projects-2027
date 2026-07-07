#include <iostream>
#include "Include/raylib/raylib.h"

auto screensize = Vector2(1280, 720);
auto center = Vector2(screensize.x/2, screensize.y/2);
class sun {
public:
    double mass = 1.9f * pow(10,30); // kg
    float radius = 695700.0f; // km

    void draw() const {
        DrawCircle(static_cast<int>(center.x), static_cast<int>(center.y), radius, YELLOW);
    }

};
class earth {
public:
    double mass = 5.9722 * 1024; // kg
    float radius = 6356.7523; //km

    void draw() const {
        DrawCircle(static_cast<int>(center.x), static_cast<int>(center.y), radius, YELLOW);
    }
};
class moon {
public:
    double mass = 7.3 * 1022; // kg
    float radius = 3474.0f; // km

    void draw() const {
        DrawCircle(static_cast<int>(center.x), static_cast<int>(center.y), radius, YELLOW);
    }
};
sun Sun;
earth Earth;
moon Moon;

double r_se = 149.6 * pow(10, 6); // distance between sun and earth
double r_em = 384400; // distance between earth and moon

int main() {
    InitWindow(1280, 720, "simulation.app");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        Earth.draw();
        Sun.draw();
        Moon.draw();

        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}