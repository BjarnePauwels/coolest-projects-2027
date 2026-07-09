#include <iostream>
#include "Include/raylib/raylib.h"
#include "Include/raylib/raymath.h"
#include "imgui/headers/imgui.h"
#include "imgui/headers/rlImGui.h"

bool CustomToggle(const char* label, bool* v, const char* label2, bool onoff = true);

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
int amount_of_slices = 1;
float angle_increment;
bool fc1 = true;

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

        DrawText("F", focalPoint1Pos.x - 4, focalPoint1Pos.y + 7, 7, GRAY); DrawText("1", focalPoint1Pos.x + 2.0f, focalPoint1Pos.y + 9, 5, GRAY);
        DrawText("F", focalPoint2Pos.x - 5, focalPoint2Pos.y + 7, 7, GRAY); DrawText("2", focalPoint2Pos.x + 1.0f, focalPoint2Pos.y + 9, 5, GRAY);

        //visualization of kepler's 2nd law
        if (visualize_2) {
            angle_increment = 360.0f / static_cast<float>(amount_of_slices);
            for (int i = 0; i < amount_of_slices; i++) {
                const float length = a;
                const float angle = angle_increment * i;
                const float angle_r = angle * PI/180;

                const float length_x = cos(angle_r) * length;
                const float length_y = sin(angle_r) * length;
                const auto end = Vector2(center.x + length_x, center.y + length_y);

                DrawLineV(fc1?focalPoint1Pos:focalPoint2Pos, end, BLUE);
            }

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

        if (ImGui::Begin("Kepler's laws", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Kepler's laws of planetary motion");
            ImGui::Checkbox("show explanation", &show_explanation);

            ImGui::SeparatorText("1st law");
            if (show_explanation) ImGui::Text("The orbit of a planet is an ellipse with the Sun at one of the two foci.");

            ImGui::SeparatorText("2nd law");
            if (show_explanation) ImGui::Text("A line segment joining a planet and the Sun sweeps out equal areas during equal intervals of time.");
            ImGui::Checkbox("visualize", &visualize_2);
            if (visualize_2) {
                ImGui::SliderInt("amount of slices", &amount_of_slices, 1, 50);
                ImGui::Text("angle increment = %f", angle_increment);
                CustomToggle("F1", &fc1, "F2", false);
            }
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

bool CustomToggle(const char* label, bool* v, const char* label2, bool onoff)
{
    ImGui::PushID(label);
    ImGui::Text(label);

    ImGui::SameLine();
    ImVec2 p = ImGui::GetCursorScreenPos();
    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f; // Adjust the width to look similar to the switch in the image

    // Colors
    ImU32 color_bg_on = ImGui::GetColorU32(ImVec4(61.0f/255.0f, 133.0f/255.0f, 224.0f/255.0f, 1.0f));  // Green when ON
    ImU32 color_bg_off = ImGui::GetColorU32(ImVec4(35.0f/255.0f, 68.0f/255.0f, 108.0f/255.0f, 1.0f)); // Red when OFF
    ImU32 color_knob = ImGui::GetColorU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f));   // White knob

    ImGui::InvisibleButton(label, ImVec2(width, height));
    bool clicked = ImGui::IsItemClicked();
    if (clicked)
        *v = !(*v); // Toggle state

    // Background
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height - 2.0f), onoff? *v ? color_bg_on : color_bg_off : color_bg_on, height * 0.5f);

    // Knob position
    float knob_radius = height * 0.3f;
    ImVec2 knob_pos = *v ? ImVec2(p.x + width - height * 0.45f, p.y + height * 0.45f) : ImVec2(p.x + height * 0.45f, p.y + height * 0.45f);

    draw_list->AddCircleFilled(knob_pos, knob_radius, color_knob);

    ImGui::PopID();

    ImGui::SameLine();
    ImGui::Text(label2);

    return clicked;
}