#pragma once
#include "pch.h"
//#include "imgui.h"
//#include "imgui_impl_sdl2.h"
//#include "imgui_impl_opengl3.h"
//#include <SDL.h>
//#include <SDL_opengl.h>
//#include <SDL_image.h>
#include "state.h"

class Interface {
public:
    Interface();
    ~Interface();

    void main();
    void boilerPlate();
    void debugMenu(AppState& state);
    void gameWindow(AppState& state);
    inline void demoWindow() { if (showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow); }

private:
    bool showDemoWindow = true;
    f32 frameRate = 0;
    u8 loadedTex = 0;
    ImGuiIO& io = ImGui::GetIO();
};