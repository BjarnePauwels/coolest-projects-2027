#include <iostream>
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "imgui/headers/imgui.h"
#include "imgui/headers/rlImGui.h"
#include "imgui/headers/rlImGuiColors.h"


typedef struct Vector2int {
    int x;                // Vector x component
    int y;                // Vector y component
} Vector2int;

class Constants {
public:
    Vector2int screensize = Vector2int(1280,720);
    const char *windowname = "simulation";

    float FPS = 60;
    bool quit_sim = false;
    Color bg_color = BLACK;

    bool show_s_app = false;
    bool show_m_app = false;
    bool show_d_app = false;

    static Vector2int cVtVI(Vector2 converting) {
        return Vector2int(static_cast<int>(converting.x),static_cast<int>(converting.y));
    }
    static Vector2 cVItV(Vector2int converting) {
        return Vector2(static_cast<float>(converting.x),static_cast<float>(converting.y));
    }
};
Constants constants;

class Simulationapp {
private:
public:
    RenderTexture ViewTexture;
    Rectangle ContentRect = { 0 };
    Camera2D camera;
    bool open = true;

    void init() {
        camera.zoom = 1;
        camera.target.x = 0;
        camera.target.y = 0;
        camera.rotation = 0;
        camera.offset.x = constants.screensize.x / 2.0f;
        camera.offset.y = constants.screensize.y / 2.0f;

        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }
    void update() {
        if (!open) return;
        BeginTextureMode(ViewTexture);
        ClearBackground(BLACK);

        DrawCircle(constants.screensize.x/2, constants.screensize.y/2, 50, YELLOW);

        EndTextureMode();
    }
    void draw() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::SetNextWindowSizeConstraints(ImVec2(400.0f, 400.0f), ImVec2(constants.screensize.x, constants.screensize.y));
        if (ImGui::Begin("simulation.app", &open, ImGuiWindowFlags_NoScrollbar)) {
            rlImGuiImageRenderTextureFit(&ViewTexture, true);
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }
    void deinit() {
        UnloadRenderTexture(ViewTexture);
    }
};
Simulationapp s_app;

class Moonphasesapp {
public:
    RenderTexture ViewTexture;
    Rectangle ContentRect = { 0 };
    Camera2D camera;
    bool open = true;

    void init() {
        camera.zoom = 1;
        camera.target.x = 0;
        camera.target.y = 0;
        camera.rotation = 0;
        camera.offset.x = constants.screensize.x / 2.0f;
        camera.offset.y = constants.screensize.y / 2.0f;

        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }
    void update() {
        if (!open) return;
        BeginTextureMode(ViewTexture);
        ClearBackground(SKYBLUE);

        DrawCircle(constants.screensize.x/2, constants.screensize.y/2, 50, YELLOW);

        EndTextureMode();
    }
    void draw() {
        if (ImGui::Begin("moonphase.app", &open, ImGuiWindowFlags_NoScrollbar)) {
            rlImGuiImageRenderTextureFit(&ViewTexture, true);
        }
        ImGui::End();
    }
    void deinit() {
        UnloadRenderTexture(ViewTexture);
    }
};
Moonphasesapp m_app;

class Dataapp {
public:
    void init() {

    }
    void update() {

    }
    void draw() {

    }
    void deinit() {}
};
Dataapp d_app;

class Interface {
private:
    static void main_menu() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Quit")) constants.quit_sim = true;

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window")) {
                if (ImGui::MenuItem("simulation.app")) constants.show_s_app = !constants.show_s_app;
                if (ImGui::MenuItem("moonphase.app")) constants.show_m_app = !constants.show_m_app;
                if (ImGui::MenuItem("data.app")) constants.show_d_app = !constants.show_d_app;

                ImGui::EndMenu();
            }
            ImGui::Text("FPS: %i", GetFPS());
            ImGui::EndMainMenuBar();
        }
    }
public:
    void init() {
        rlImGuiSetup(true);
    }
    void update() {

    }
    void draw() {
        rlImGuiBegin();

        main_menu();

        // simulation.app
        if (constants.show_s_app) s_app.draw();
        // moonphase.app
        if (constants.show_m_app) m_app.draw();
        // data.app
        if (constants.show_d_app) d_app.draw();

        rlImGuiEnd();
    }
    void deinit() {
        rlImGuiShutdown();
    }
};

Interface imgui;

class Simulation {
private:
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

        s_app.init();
    }
    static void update() {
        checkDeinit();

        s_app.update();

        imgui.update();
    }
    static void draw() {
        BeginDrawing();

        clearScreen();

        imgui.draw();

        EndDrawing();
    }
    static int deinit() {
        imgui.deinit();

        s_app.deinit();

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