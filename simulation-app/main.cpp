#include <iostream>
#include "Include/raylib/raylib.h"
#include "imgui/headers/imgui.h"
#include "imgui/headers/rlImGui.h"

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
    float radius = 6371; //km

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

double r_se_max = 152098233; // max distance between sun and earth
double r_se_min = 147098291; // min distance between sun and earth

double r_em = 384400; // distance between earth and moon

float semi_mayor_axis = screensize.x/3;
float semi_minor_axis = screensize.y/3;

int main() {
    InitWindow(1280, 720, "simulation.app");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        


        float V = semi_minor_axis;
        float H = semi_mayor_axis;

        DrawEllipseLines(static_cast<int>(center.x), static_cast<int>(center.y), H, V, RAYWHITE);

        //Earth.draw();
        //Sun.draw();
        //Moon.draw();

        //imgui
        rlImGuiBegin();

        if (ImGui::Begin("orbit")) {
            ImGui::Text("ellipse");
            ImGui::SliderFloat("a", &semi_mayor_axis, 0.0f, screensize.x/2);
            ImGui::SliderFloat("b", &semi_minor_axis, 0.0f, screensize.y/2);
        }ImGui::End();

        rlImGuiEnd();

        EndDrawing();
    }
    rlImGuiShutdown();

    CloseWindow();
    return 0;
}