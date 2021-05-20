#include <iostream>
#include "display/game_window.hpp"

using namespace std;

int main() {
    BaseWindow* bw = new GameWindow(1280, 720, "raylib-imgui-cmake-template by @dcronqvist");
    bw->Run();
    return 0;
}