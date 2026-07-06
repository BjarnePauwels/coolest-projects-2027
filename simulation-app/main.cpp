#include <iostream>
#include "Include/raylib/raylib.h"

class sun {
public:

};
class earth {
public:

};
class moon {
public:

};

int main() {
    InitWindow(1280, 720, "simulation.app");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        

        ClearBackground(BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}