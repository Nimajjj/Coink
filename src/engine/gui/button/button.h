//
// Created by Ben on 24/07/2022.
//

#ifndef ENGINE_BUTTON_H
#define ENGINE_BUTTON_H
#include <iostream>
#include <string>
#include <SDL.h>
#include "../../types.h"


class Button {
public:
    std::string value;
    vec2 position;
    vec2 size;
    unsigned font_size;
    Color bg_color;
    Color outline_color;

    Button(void (*act)(), std::string val, unsigned ft_size, int x, int y, int w, int h);
    ~Button() = default;

    void Press();

private:
    void (*action)();
};


#endif //ENGINE_BUTTON_H
