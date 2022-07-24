//
// Created by Ben on 24/07/2022.
//

#include "gui.h"

GUI::GUI(){
    last_mouse_state = 0;
}

GUI::~GUI() {
    Close();
}

void GUI::Close() {

}

void GUI::Display(Render* render) {
    for (auto button: buttons) {
        double delta = button.font_size / 64.0;
        render->DrawFillRect(
                button.position.x,
                button.position.y,
                button.size.x,
                button.size.y,
                button.bg_color
                );

        render->DrawRect(
                button.position.x,
                button.position.y,
                button.size.x,
                button.size.y,
                button.outline_color
                );

        render->Print(
                button.value,
                button.position.x + (button.font_size / 2),
                button.position.y,
                button.font_size
                );
    }
}

void GUI::UpdateButtons() {
    int x, y;

    SDL_PumpEvents();
    Uint32 mouse_state = SDL_GetMouseState(&x, &y);

    if ((mouse_state & SDL_BUTTON_LMASK) != 0 && last_mouse_state == 0) {
        for (auto button : buttons) {
            if( button.position.x < x &&
                button.position.x + button.size.x > x &&
                button.position.y < y &&
                button.position.y + button.size.y > y)
            {
                button.Press();
            }
        }
        last_mouse_state = mouse_state;
    } else if (last_mouse_state != 0 && mouse_state == 0 ) {
        last_mouse_state = 0;
    }
}

Button* GUI::ButtonNew(void (*act)(), std::string val, unsigned ft_size,  int x, int y, int w, int h) {
    buttons.push_back(Button(act, val, ft_size, x, y, w, h));
    return &buttons.back();
}