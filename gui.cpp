#include "gui.hpp"
#include "globals.hpp"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>

Gui::Gui()
{
    BOOST_LOG_TRIVIAL(info) << "Initialize Window..." << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        BOOST_LOG_TRIVIAL(fatal) << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    } else {
        _mainWindow = SDL_CreateWindow(
            "ETF Emulator",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if (_mainWindow == NULL) {
            BOOST_LOG_TRIVIAL(fatal) << "SDL window could not be initialize! SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            _screenSurface = SDL_GetWindowSurface(_mainWindow);
            SDL_FillRect(
                _screenSurface,
                NULL,
                SDL_MapRGB(_screenSurface->format,0xFF,0xFF,0xFF)
            );

            SDL_UpdateWindowSurface(_mainWindow);
            SDL_Delay(20000);
        }
    }


}