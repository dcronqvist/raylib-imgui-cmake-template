#pragma once

#include "raylib-cpp/raylib-cpp.hpp"
#include "display/base_window.hpp"


class GameWindow : public BaseWindow {
private:
    RenderTexture2D renTexUI;
    Rectangle uiSourceRectangle;

public:
    GameWindow(int w, int h, std::string title) : BaseWindow(w, h, title) {};
    void Initialize();
    void LoadContent();
    void Update();
    void Render();
    void Unload();
};