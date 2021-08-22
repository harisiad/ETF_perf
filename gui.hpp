#ifndef __GUI_HPP__
#define __GUI_HPP__

#include "globals.hpp"
#include "invest.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Gui
{
    private:
    SDL_Window* _mainWindow;
    SDL_Surface* _screenSurface;
    SDL_Renderer* _renderer;
    SDL_Event _eventHanlder;
    SDL_GLContext _glContext;
    TTF_Font* _textFont;
    SDL_Color _black;

    struct _initializers {
        int sdlInit;
    }_initializers;

    struct _events {
        bool quit = false;
    }_events;

    Invest* _investmentBL;
    std::string _textToUi;

    public:
    Gui(Invest* investmentBL);
    ~Gui();

    void run();
    void windowInit();
    void handleEvents();
};

#endif //__GUI_HPP__