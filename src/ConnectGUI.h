#ifndef CONNECTGUI_H
#define CONNECTGUI_H
#include "BoardManager.h"
#include "gwindow.h"
#include <vector>


using namespace sgl;

int static TILESIZE = 50;
int static OFFSET = 5;
vector<string> static CONNECTCOUNT = {"3", "4", "5"};

class ConnectGUI{
private:
    BoardManager* manager;
    Board* board;
    GWindow* window;
    void makeMenu();
public:
    ConnectGUI();
    void redraw();
    BoardManager* getBoardManager() const;
    GWindow* getWindow() const;
    string getWinner() const;
};


#endif // CONNECTGUI_H
