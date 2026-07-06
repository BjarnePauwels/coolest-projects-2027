#include <iostream>
#include "raylib/raylib.h"
#include "imgui/headers/imgui.h"
#include "imgui/headers/rlImGui.h"

typedef struct Vector2int {
    int x;                // Vector x component
    int y;                // Vector y component
    static Vector2int cVtVI(Vector2 converting) {
        return Vector2int(static_cast<int>(converting.x),static_cast<int>(converting.y));
    }
    static Vector2 cVItV(Vector2int converting) {
        return Vector2(static_cast<float>(converting.x),static_cast<float>(converting.y));
    }
} Vector2int;

class Constants {
public:
    Vector2int screensize = Vector2int(640,480);
    const char *windowname = "simulation";

    float FPS = 60;
    bool quit_sim = false;
    Color bg_color = BLACK;
};
Constants constants;


//...

class Interface {
private:

public:
    void init() {

    }
    void update() {

    }
    void draw() {

    }
    void deinit() {

    }
};

Interface imgui;

class Simulation {
private:
    static void drawFPS() {
        const char* fps = TextFormat("fps: %i", GetFPS());
        DrawText(fps, 10, 10, 15, WHITE);
    }
    static void checkDeinit() {
        if (WindowShouldClose()) constants.quit_sim = true;
    }
    static void clearScreen() {
        ClearBackground(constants.bg_color);
    }
public:

    static void init() {
        InitWindow(constants.screensize.x,constants.screensize.y, constants.windowname);

        SetTargetFPS(constants.FPS);

        imgui.init();
    }
    static void update() {
        checkDeinit();

        imgui.update();

    }
    static void draw() {
        BeginDrawing();

        clearScreen();
        drawFPS();

        imgui.draw();

        EndDrawing();
    }
    static int deinit() {
        imgui.deinit();

        CloseWindow();
        return 0;
    }
};

int main()
{
    Simulation::init();

    while (!constants.quit_sim) {
        Simulation::update();

        Simulation::draw();
    }

    Simulation::deinit();
}