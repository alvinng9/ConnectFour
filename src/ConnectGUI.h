#ifndef CONNECTGUI_H
#define CONNECTGUI_H
#include "BoardManager.h"
#include "gwindow.h"
#include <vector>
#include "gbutton.h"
#include "gtextfield.h"


using namespace sgl;

int static TILESIZE = 50;
int static OFFSET = 5;
vector<string> static COLOR = {"red", "blue", "green", "purple", "cyan", "brown", "orange"};

class ConnectGUI{
private:
    BoardManager* manager;
    Board* board;
    GWindow* window;
    void makeMenu();
    string colorP1;
    string colorP2;
    //int numTile;
    void makeSliders();
    GButton* makeColorChooser(string& color);
    GTextField* playerName(string player);
    void toggle(bool setEnable);
    void loadGame();
    void lowerPiece();
    void checkWinner();
    vector<int> statsGame;
public:
    ConnectGUI();
    void redraw();
    BoardManager* getBoardManager() const;
    string getWinner() const;
};


#endif // CONNECTGUI_H
