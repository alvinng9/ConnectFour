#ifndef CONNECTGUI_H
#define CONNECTGUI_H
#include "BoardManager.h"
#include "gwindow.h"

using namespace sgl;

int static TILESIZE = 50;
int static OFFSET = 5;

class ConnectGUI{
private:
    BoardManager* manager;
    Board* board;
    GWindow* window;

public:
    ConnectGUI();
    void redraw();
    void clickHandler();

};

#endif // CONNECTGUI_H
