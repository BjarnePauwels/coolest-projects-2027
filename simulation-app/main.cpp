#include <iostream>
#include "Include/raylib/raylib.h"
#include "Include/raylib/raymath.h"
#include "imgui/headers/imgui.h"
#include "imgui/headers/rlImGui.h"

auto screensize = Vector2(1280, 720);
auto center = Vector2(screensize.x/2, screensize.y/2);

float calculate_a(const float c, const float e) {
    const float a = c/e;
    return a;
}
float calculate_b(const float a, const float c) {
    const double b = sqrt(pow(a, 2) - pow(c, 2));
    return static_cast<float>(b);
}
float calculate_c(const float a, const float e, const float b = 0) {
    double c = 0;
    if (b == 0 && e != 0) {
        c = e * a;
    }
    if (b != 0 && e == 0) {
        c = sqrt(pow(a, 2) - pow(b, 2));
    }
    return static_cast<float>(c);
}


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

float a = semi_mayor_axis, b = semi_minor_axis, c, e; // semi-mayor-axis, semi-minor-axis, distance focalpoint & center, eccentricity
float a_max = screensize.x/2;
float b_max = screensize.y/2;

bool show_explanation = false;
bool visualize_2 = false;

void update_axis(const float _a, const float _b) {
    semi_mayor_axis = _a;
    semi_minor_axis = _b;
}

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

        float _c = calculate_c(a, 0.0f, b);
        const auto focalPoint1Pos = Vector2(center.x + _c, center.y);
        DrawCircleV(focalPoint1Pos, 2, RAYWHITE);
        const auto focalPoint2Pos = Vector2(center.x - _c, center.y);
        DrawCircleV(focalPoint2Pos, 2, RAYWHITE);

        // line_indecation
        DrawLineV(center, focalPoint1Pos, GRAY);
        DrawText("c", static_cast<int>(focalPoint1Pos.x - _c/2), static_cast<int>(focalPoint1Pos.y - 10), 5, GRAY);

        DrawLineV(Vector2(center.x, center.y + 5), Vector2(center.x + a, center.y + 5), GRAY);
        DrawText("a", static_cast<int>(center.x + a/2), static_cast<int>(center.y + 5), 5, GRAY);

        DrawLineV(center, Vector2(center.x, center.y - b), GRAY);
        DrawText("b", static_cast<int>(center.x - 8), static_cast<int>(center.y - b/2), 5, GRAY);

        //visualization of kepler's 2nd law
        if (visualize_2) {
            
        }

        //Earth.draw();
        //Sun.draw();
        //Moon.draw();

        //imgui
        rlImGuiBegin();
        if (ImGui::Begin("orbit", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("ellipse");

            static const char* items[]{"a & b","a & c","a & e", "c & e"};
            static int selected_item = 0;
            if (!ImGui::Combo("specify points", &selected_item, items, IM_ARRAYSIZE(items)))
            {
                if (selected_item == 0) {
                    ImGui::SliderFloat("a", &a, b, a_max);
                    if (a < b) a = b;
                    ImGui::SliderFloat("b", &b, 0.0f, b_max);

                    update_axis(a,b);
                    semi_mayor_axis = a;
                    semi_minor_axis = b;
                }
                if (selected_item == 1) {
                    ImGui::SliderFloat("a", &a, c, b_max);
                    if (c > a) c = a;
                    ImGui::SliderFloat("c", &c, 0.0f, a);

                    b = calculate_b(a, c);
                    update_axis(a,b);
                }
                if (selected_item == 2) {
                    ImGui::SliderFloat("a", &a, 0.0f, b_max);
                    ImGui::SliderFloat("e", &e, 0.0f, 1.0f);

                    c = calculate_c(a, e);
                    b = calculate_b(a, c);
                    update_axis(a,b);
                }
                if (selected_item == 3) {
                    ImGui::SliderFloat("c", &c, 0.0f, static_cast<float>(sqrt(pow(a_max, 2) - pow(b_max, 2))));
                    ImGui::SliderFloat("e", &e, c/a_max, 1.0f);
                    if (e < c/a_max) e = c/a_max;

                    a = calculate_a(c, e);
                    b = calculate_b(a, c);
                    update_axis(a,b);
                }
            }

        }
        ImGui::End();

        if (ImGui::Begin("Kepler's laws", nullptr)) {
            ImGui::Text("Kepler's laws of planetary motion");
            ImGui::Checkbox("show explanation", &show_explanation);

            ImGui::SeparatorText("1st law");
            if (show_explanation) ImGui::Text("The orbit of a planet is an ellipse with the Sun at one of the two foci.");

            ImGui::SeparatorText("2nd law");
            if (show_explanation) ImGui::Text("A line segment joining a planet and the Sun sweeps out equal areas during equal intervals of time.");
            ImGui::Checkbox("visualize", &visualize_2);

            ImGui::SeparatorText("3rd law");
            if (show_explanation) ImGui::Text("The square of a planet's orbital period is proportional to the cube of the length of the semi-major axis of its orbit.");
            ImGui::Text("T² ∞ a³");
        }
        ImGui::End();

        ImGui::Render();
        ImGui::EndFrame();

        rlImGuiEnd();

        EndDrawing();

    }

    rlImGuiShutdown();

    CloseWindow();
    return 0;
}