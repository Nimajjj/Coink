//
// Created by Ben on 24/07/2022.
//

#include "button.h"

Button::Button(void (*act)(), std::string val, unsigned ft_size, int x, int y, int w, int h) :
    action(act),
    value(val),
    position(vec2(x, y)),
    size(vec2(w, h)),
    font_size(ft_size),
    bg_color(Color(0x22, 0x1F, 0x22)),
    outline_color(Color(COLOR_WHITE))
{}

void Button::Press() {
    (*action)();
}