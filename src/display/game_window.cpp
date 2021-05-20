#include "raylib-cpp/raylib-cpp.hpp"
#include "display/game_window.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_raylib.h"
#include "utils/utility.hpp"
#include <string>
#include <random>

Vector2 helloPos;
Vector2 helloVel;

void GameWindow::Initialize() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI); // Optional

    // TEMPLATE STUFF (YOU CAN REMOVE THIS)
    helloPos = { 1280 / 3, 720 / 4 };
    helloVel = { 100, 100 };
}

void GameWindow::LoadContent() {
    // Fix high dpi font
    SetTextureFilter(GetFontDefault().texture, FILTER_POINT);
    SetTargetFPS(0);

    // Init imgui
    ImGui_ImplRaylib_Init(this->windowWidth, this->windowHeight, { "" }, 16.0F);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 3);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);

    // Fix UI render texture
    this->renTexUI = LoadRenderTexture(this->windowWidth, this->windowHeight);
    this->uiSourceRectangle = { 0, static_cast<float>(windowHeight), static_cast<float>(this->windowWidth), static_cast<float>(-(this->windowHeight)) };
}

void GameWindow::Update() {
    if (this->FocusingWindow()) {
        SetTargetFPS(0);
    }
    if (this->UnfocusingWindow()) {
        SetTargetFPS(15);
    }

    // TODO: HERE YOU CAN PUT GAME/APPLICATION LOGIC

    helloPos = { helloPos.x + helloVel.x * GetFrameTime(), helloPos.y + helloVel.y * GetFrameTime() };

    if (helloPos.x < 0) {
        helloVel = { -helloVel.x, helloVel.y };
    }
    if (helloPos.x > this->windowWidth) {
        helloVel = { -helloVel.x, helloVel.y };
    }
    if (helloPos.y < 0) {
        helloVel = { helloVel.x, -helloVel.y };
    }
    if (helloPos.y > this->windowHeight) {
        helloVel = { helloVel.x, -helloVel.y };
    }
}

void SubmitUI(GameWindow& window) {
    // TODO: USE IMGUI TO DISPLAY UI
    ImGui::ShowDemoWindow();
}

void GameWindow::Render() {

    // Draw UI to a RenderTexture2D
    BeginTextureMode(renTexUI); {
        ClearBackground(BLANK);
        ImGui_ImplRaylib_NewFrame();
        ImGui_ImplRaylib_ProcessEvent();
        ImGui::NewFrame();

        SubmitUI(*this);

        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();
        raylib_render_imgui(draw_data);
        EndTextureMode();
    }

    // Begin drawing to screen
    BeginDrawing();
    // Clear to a black background color
    ClearBackground(BLACK);

    // TODO: DRAW GAME/APPLICATION STUFF HERE

    DrawText("Hello World!", (int)helloPos.x, (int)helloPos.y, 14, WHITE);

    // Draw UI rendertexture to screen. uiSourceRectangle is a 
    // source rec that is specified to be upside down, since rendering
    // actually takes place upside down when rendering to texture.
    DrawTextureRec(renTexUI.texture, uiSourceRectangle, { 0, 0 }, WHITE);

    //DrawFPS(10, 10);

    EndDrawing();
}

void GameWindow::Unload() {}