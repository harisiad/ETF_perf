#include "textBoxGui.hpp"

TextBoxGUI::TextBoxGUI()
{
    _textBoxSurface = new SDL_Surface();
    _black = {0,0,0};
}

TextBoxGUI::~TextBoxGUI()
{
    SDL_FreeSurface(_textBoxSurface);
}

SDL_Surface* TextBoxGUI::getTextBoxSurface() 
{
    return _textBoxSurface;
}

void TextBoxGUI::setup(
    boost::container::vector<std::string> data,
    SDL_Renderer* renderer,
    TTF_Font* textFont,
    SDL_Color black
) {
    int w = 0, h = 0;

    for (std::string str : data) {
        textSurface.push_back(TTF_RenderText_Solid(
            textFont,
            str.c_str(),
            black
        ));

        text.push_back(SDL_CreateTextureFromSurface(renderer, textSurface.back()));
        
        SDL_Rect tmpBox;
        tmpBox.x = (SCREEN_WIDTH / 5);
        tmpBox.y = w;
        tmpBox.w = textSurface.back()->w;
        tmpBox.h = textSurface.back()->h;

        textBox.push_back(tmpBox);
        w += 16;
        h += 16;
    }
}

void TextBoxGUI::display(SDL_Renderer* renderer, SDL_Surface* screenSurface)
{
    for (int i = 0; i < textBox.size(); i++) {
        SDL_RenderFillRect(renderer, &textBox[i]);
        SDL_BlitSurface(screenSurface, NULL, textSurface[i], &textBox[i]);
        SDL_RenderCopy(renderer, text[i], NULL, &textBox[i]);
    }
}
