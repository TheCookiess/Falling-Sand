#pragma once
#include "game.h"
#include "interface.h"
#include "state.h"
#include <SDL.h>

class Framework {
public:
    Framework();  // Constructor
    ~Framework(); // Deconstructor

    bool init(const char* title, int xpos, int ypos, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();

    inline bool running() const { return applicationRunning; } // const means this function cannot modify any member variables

private:
    void loadImageRGB(TextureData& texture, std::string& path);
    void loadImageRGBA(TextureData& texture, std::string& path); // png is somehow rgb not rgba..

    void saveChangesToFile(std::string& name, std::vector<std::pair<u16, u16>> changedCells);
    void loadChangesFromFile(std::string& name);

    void saveSimToFile(std::string& name);
    void loadSimFromFile(std::string& name);

    void createTexture(TextureData& texture);
    void updateTexture(TextureData& texture);
    void reloadTextures();

    void mouseDraw();

    void startAnimation();


    std::vector<std::string> split(const std::string& s, char delim);

    /*----------------------------------------------------------------
   ---- Variables ---------------------------------------------------
   ----------------------------------------------------------------*/


    bool applicationRunning = false;

    AppState      state;                // consolidated shared state into a structure.
    Game*         game       = nullptr; // std::unique_ptr<Game>
    Interface*    interface  = nullptr; // std::unique_ptr<Interface>
    SDL_Window*   window     = nullptr; // could use a unique ptr but would require a refactor,
    SDL_GLContext gl_context = nullptr; // thats too much effort for some 'useless' memory safety.
};
