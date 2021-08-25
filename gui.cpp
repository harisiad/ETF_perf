#include "gui.hpp"

#include <boost/log/core.hpp>
#include <boost/container/vector.hpp>
#include <boost/log/trivial.hpp>
#include <iostream>

#define GLEW_STATIC
#include <GL/gl.h>

Gui::Gui(Invest* investmentBL):
_investmentBL(investmentBL)
{
    BOOST_LOG_TRIVIAL(info) << "Initialize Window..." << std::endl;

    _initializers.sdlInit = SDL_Init(SDL_INIT_VIDEO);
    _black = {0,0,0};
}

Gui::~Gui()
{
    BOOST_LOG_TRIVIAL(info) << "Destroying renderer" << std::endl;
    SDL_DestroyRenderer(_renderer);
    // BOOST_LOG_TRIVIAL(info) << "Destroying surface" << std::endl;
    // SDL_FreeSurface(_screenSurface);

    BOOST_LOG_TRIVIAL(info) << "Destroying window" << std::endl;
    SDL_DestroyWindow( _mainWindow );

    BOOST_LOG_TRIVIAL(info) << "SDL Quit" << std::endl;
    SDL_Quit();
}

void Gui::run()
{
    boost::container::vector<SDL_Surface*> textSurface;
    boost::container::vector<SDL_Texture*> text;
    boost::container::vector<SDL_Rect> textBox;
    int w = 0, h = 0;

    if ( _initializers.sdlInit < 0) {
        BOOST_LOG_TRIVIAL(fatal) << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        windowInit();
    }

    _textFont = TTF_OpenFont("roboto_regular.ttf", 10);

    for (std::string str : _investmentBL->run()) {
        textSurface.push_back(TTF_RenderText_Solid(
            _textFont,
            str.c_str(),
            _black
        ));

        text.push_back(SDL_CreateTextureFromSurface(_renderer, textSurface.back()));
        
        SDL_Rect tmpBox;
        tmpBox.x = (SCREEN_WIDTH / 5);
        tmpBox.y = w;
        tmpBox.w = textSurface.back()->w;
        tmpBox.h = textSurface.back()->h;

        textBox.push_back(tmpBox);
        w += 16;
        h += 16;
    }

    SDL_StartTextInput();
    while (!_events.quit) {
        
        SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear(_renderer);

        for (int i = 0; i < textBox.size(); i++) {
            SDL_RenderFillRect(_renderer, &textBox[i]);
            SDL_BlitSurface(_screenSurface, NULL, textSurface[i], &textBox[i]);
            SDL_RenderCopy(_renderer, text[i], NULL, &textBox[i]);
        }

        SDL_RenderPresent(_renderer);
        handleEvents();
        //SDL_UpdateWindowSurface(_mainWindow);
    }
    SDL_StopTextInput();
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
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        BOOST_LOG_TRIVIAL(fatal) << "Linear texture filtering not enabled! SDL_Error: " << SDL_GetError() << std::endl;
    }

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
        } else {
            //Initialize renderer color
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }

        BOOST_LOG_TRIVIAL(info) << "Initialize GL Context..." << std::endl;
        _glContext = SDL_GL_CreateContext(_mainWindow);

        if (TTF_Init() == -1) {
            BOOST_LOG_TRIVIAL(fatal) << "SDL TTF could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
}