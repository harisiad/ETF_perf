#ifndef __TEXTBOXGUI_HPP__
#define __TEXTBOXGUI_HPP__

#include "globals.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <boost/container/vector.hpp>

class TextBoxGUI
{
    private:
    SDL_Surface* _textBoxSurface;
    SDL_Color _black;
    boost::container::vector<SDL_Surface*> textSurface;
    boost::container::vector<SDL_Texture*> text;
    boost::container::vector<SDL_Rect> textBox;

    public:
    TextBoxGUI();
    ~TextBoxGUI();

    SDL_Surface* getTextBoxSurface();
    void setup(
        boost::container::vector<std::string>,
        SDL_Renderer*,
        TTF_Font*,
        SDL_Color
    );
    void display(SDL_Renderer*,SDL_Surface*);
};

#endif