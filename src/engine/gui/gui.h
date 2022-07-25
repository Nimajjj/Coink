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

/*
 * TODO :
 *  - Make a proper Text class which don't need to be redraw each frame ... flemme
 *  - Delete method for each class lol
 *  - Text box
 */


class GUI {
public:
    GUI();
    ~GUI();
    void Close();

    void Display(Render* render);

    void UpdateButtons();
    Button* ButtonNew(void (*act)(), const std::string& val, const unsigned& ft_size, const int& x, const int& y, const int& w = 0, const int& h = 0);
    void ButtonDelete(Button* bt_to_delete);

private:
    Uint32 last_mouse_state;
    std::vector<Button*> buttons;
};


#endif //ENGINE_GUI_H
