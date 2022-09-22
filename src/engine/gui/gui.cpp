//
// Created by Ben on 24/07/2022.
//

#include "gui/gui.h"

Uint32 last_mouse_state;
std::vector<Button*> buttons;

void GuiInit() {
    last_mouse_state = 0;
}

void GuiClose() {
    for ( auto &button : buttons ) {
        delete button;
        button = nullptr;
    }
    buttons.clear();
}

void GuiDisplay() {
    for ( const auto &button: buttons ) {
        DrawFillRect(
                button->position.x,
                button->position.y,
                button->size.x,
                button->size.y,
                button->bg_color
                );

        DrawRect(
                button->position.x,
                button->position.y,
                button->size.x,
                button->size.y,
                button->outline_color
                );

        ScreenPrint(
                button->value,
                button->position.x + (button->font_size / 2),
                button->position.y,
                button->font_size
                );
    }
}

void UpdateButtons() {
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

Button* ButtonNew(void (*act)(), const std::string& val, const unsigned& ft_size, const int& x, const int& y, const int& w, const int& h) {
    int width = w;
    int height = h;
    if ( w == 0 || h == 0 ) {
        SDL_Surface* surface = TTF_RenderText_Solid( GetFont(), val.c_str(), {0xFF,0xFF,0xFF} );
        double delta = ft_size / 64.0;
        if ( w == 0 ) {
            width = surface->w * delta + ft_size;
        }
        if (h == 0) {
            height = surface->h * delta;
        }
        SDL_FreeSurface( surface );
    }

    Button* bt = new Button( act, val, ft_size, x, y, width, height );
    buttons.push_back( bt );
    return bt;
}

void ButtonDelete(Button* bt_to_delete) {
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