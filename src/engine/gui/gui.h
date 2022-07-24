//
// Created by Ben on 24/07/2022.
//

#ifndef ENGINE_GUI_H
#define ENGINE_GUI_H
#include <string>
#include <vector>
#include <SDL.h>
#include "../render/render.h"
#include "button/button.h"

class GUI {
public:
    GUI();
    ~GUI();
    void Close();

    void Display(Render* render);

    void UpdateButtons();

    Button* ButtonNew(void (*act)(), std::string val, unsigned ft_size, int x, int y, int w = 0, int h = 0);

private:
    std::vector<Button> buttons;

    Uint32 last_mouse_state;
};


#endif //ENGINE_GUI_H
