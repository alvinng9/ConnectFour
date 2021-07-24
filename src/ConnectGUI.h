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
    void guiText();

public:
    ConnectGUI();
    void redraw();
    //void setClickHandler(actionFunc func);
    BoardManager* getBoardManager() const;
};

typedef void (*actionFunc)(GEvent);

void setClickHandler(actionFunc func);

//void clickHandler(GEvent mouseEvent);

#endif // CONNECTGUI_H
