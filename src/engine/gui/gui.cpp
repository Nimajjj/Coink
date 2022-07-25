//
// Created by Ben on 24/07/2022.
//

#include "gui.h"

GUI::GUI() :
    last_mouse_state(0)
{}

GUI::~GUI() {
    Close();
}

void GUI::Close() {
    for ( auto &button : buttons ) {
        delete button;
        button = nullptr;
    }
    buttons.clear();
}

void GUI::Display(Render* render) {
    for ( const auto &button: buttons ) {
        render->DrawFillRect(
                button->position.x,
                button->position.y,
                button->size.x,
                button->size.y,
                button->bg_color
                );

        render->DrawRect(
                button->position.x,
                button->position.y,
                button->size.x,
                button->size.y,
                button->outline_color
                );

        render->Print(
                button->value,
                button->position.x + (button->font_size / 2),
                button->position.y,
                button->font_size
                );
    }
}

void GUI::UpdateButtons() {
    int x, y;

    SDL_PumpEvents();
    Uint32 mouse_state = SDL_GetMouseState( &x, &y );

    if ( ( mouse_state & SDL_BUTTON_LMASK ) != 0 && last_mouse_state == 0 ) {
        for (auto button : buttons) {
            if( button->position.x < x &&
                button->position.x + button->size.x > x &&
                button->position.y < y &&
                button->position.y + button->size.y > y)
            {
                button->Press();
            }
        }
        last_mouse_state = mouse_state;
    } else if ( last_mouse_state != 0 && mouse_state == 0 ) {
        last_mouse_state = 0;
    }
}

Button* GUI::ButtonNew(void (*act)(), const std::string& val, const unsigned& ft_size, const int& x, const int& y, const int& w, const int& h) {
    Button* bt = new Button( act, val, ft_size, x, y, w, h );
    buttons.push_back( bt );
    return bt;
}

void GUI::ButtonDelete(Button* bt_to_delete) {
    unsigned index = -1;
    for ( unsigned i = 0; i < buttons.size(); i++ ) {
        if ( buttons[i] == bt_to_delete ) {
            index = i;
            break;
        }
    }

    if ( index == -1 ) {
        return;
    }

    delete buttons[index];
    buttons.erase( buttons.begin() + index );
}