#ifndef __GUI_HPP__
#define __GUI_HPP__

#include "globals.hpp"

#include <SDL2/SDL.h>

class Gui
{
    private:
    SDL_Window* _mainWindow;
    SDL_Surface* _screenSurface;

    public:
    Gui();
};

#endif