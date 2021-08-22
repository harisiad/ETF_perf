#include "gui.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>

#define GLEW_STATIC
#include <GL/gl.h>

Gui::Gui(Invest* investmentBL):
_investmentBL(investmentBL)
{
    BOOST_LOG_TRIVIAL(info) << "Initialize Window..." << std::endl;

    _initializers.sdlInit = SDL_Init(SDL_INIT_VIDEO);
    _textFont = TTF_OpenFont("roboto_regular.ttf", 10);
    _black = {0,0,0};
}

Gui::~Gui()
{
    BOOST_LOG_TRIVIAL(info) << "Destroying surface" << std::endl;
    SDL_FreeSurface(_screenSurface);

    BOOST_LOG_TRIVIAL(info) << "Destroying window" << std::endl;
    SDL_DestroyWindow( _mainWindow );

    BOOST_LOG_TRIVIAL(info) << "SDL Quit" << std::endl;
    SDL_Quit();
}

void Gui::run()
{
    if ( _initializers.sdlInit < 0) {
        BOOST_LOG_TRIVIAL(fatal) << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        windowInit();
    }
    std::string tmpPlaceholder;
    for (std::string str : _investmentBL->run()) {
        tmpPlaceholder = _textToUi + str + "\n";

        _textToUi = tmpPlaceholder;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(
        _textFont,
        _textToUi.c_str(), 
        _black
    );

    SDL_Texture* text = SDL_CreateTextureFromSurface(_renderer, textSurface);
    SDL_Rect textBox;
    textBox.x = 0;
    textBox.y = 0;
    textBox.w = 10;
    textBox.h = 10;

    SDL_StartTextInput();
    while (!_events.quit) {
        
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(_renderer);

        SDL_RenderFillRect(_renderer, &textBox);
        SDL_BlitSurface(_screenSurface, NULL, textSurface, &textBox);
        SDL_RenderCopy(_renderer, text, NULL, &textBox);

        SDL_RenderPresent(_renderer);
        handleEvents();
        //SDL_UpdateWindowSurface(_mainWindow);
    }
    SDL_StopTextInput;
}

void Gui::handleEvents()
{
    while (SDL_PollEvent(&_eventHanlder) != 0) {
        if (_eventHanlder.type == SDL_QUIT) {
            _events.quit = true;
        }
    }
}

void Gui::windowInit()
{
    BOOST_LOG_TRIVIAL(info) << "Create Window..." << std::endl;
    _mainWindow = SDL_CreateWindow(
            "ETF Performance",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );

    if (_mainWindow == NULL) {
        BOOST_LOG_TRIVIAL(fatal) << "SDL window could not be initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        BOOST_LOG_TRIVIAL(info) << "Creating Renderer..." << std::endl;
        _renderer = SDL_CreateRenderer(
            _mainWindow, 
            -1, 
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );
        
        if (_renderer == NULL) {
            BOOST_LOG_TRIVIAL(fatal) << "SDL renderer could not be initialize! SDL_Error: " << SDL_GetError() << std::endl;
        }

        BOOST_LOG_TRIVIAL(info) << "Initialize GL Context..." << std::endl;
        _glContext = SDL_GL_CreateContext(_mainWindow);

        BOOST_LOG_TRIVIAL(info) << "Creating Surface..." << std::endl;
        _screenSurface = SDL_GetWindowSurface(_mainWindow);

        if (_screenSurface == NULL) {
            BOOST_LOG_TRIVIAL(fatal) << "SDL surfacing could not be initialize! SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
}