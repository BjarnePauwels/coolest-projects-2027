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

class constants {
    public:

};


class interface {
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

interface imgui;

class simulation {
public:

    void init() {


        imgui.init();
    }
    void update() {
        imgui.update();

    }
    void draw() {
        imgui.draw();

    }
    void deinit() {
        imgui.deinit();

    }
};

int main()
{
}