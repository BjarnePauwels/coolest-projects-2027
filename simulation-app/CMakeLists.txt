cmake_minimum_required(VERSION 4.2)
project(simulation_app)

set(CMAKE_CXX_STANDARD 20)
set(raylib_DIR Libraries/raylib/cmake/raylib)

find_package(raylib REQUIRED PATHS Libraries/raylib/cmake/ NO_DEFAULT_PATH)
include_directories(Include/
        Include/raylib/
        Include/imgui/headers/)

add_executable(simulation_app
        Include/imgui/imgui.cpp
        Include/imgui/imgui_demo.cpp
        Include/imgui/imgui_draw.cpp
        Include/imgui/imgui_tables.cpp
        Include/imgui/imgui_widgets.cpp
        Include/imgui/rlImGui.cpp
        main.cpp)
target_link_libraries(simulation_app raylib)