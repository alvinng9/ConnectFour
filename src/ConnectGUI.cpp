#include "ConnectGUI.h"
#include <iomanip>
#include "gthread.h"
#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
#include "gobjects.h"
#include "gradiobutton.h"
#include "gtextfield.h"

actionFunc funcHighlight = nullptr;

GButton* btnDrop;
GTextField* txtDrop;
GLabel* lblWin;

ConnectGUI::ConnectGUI(){
    window = new GWindow(400,300);
    board = new Board(6,6);
    manager = new BoardManager(board);
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    window->setTitle("Connect Four");
    cout << "test pre setclick" << endl;
    //window->setClickListener(funcHighlight);
    cout << "test post setclick" << endl;
    guiText();
    redraw();
}

void ConnectGUI::redraw(){
    for (int i = 0; i < board->getRows(); i++){
        for(int j = 0; j < board->getCols(); j++){
            string pieceHere = board->getPiece(i,j);
            if (pieceHere == ""){
                window->setColor("white");
            } else if (pieceHere == "P1"){
                window->setColor("blue");
            } else {
                window->setColor("red");
            }
            window->fillOval(j * TILESIZE + OFFSET, (board->getRows() - i - 1) * TILESIZE + OFFSET, TILESIZE - OFFSET * 2, TILESIZE - OFFSET * 2);
        }
    }
    window->repaint();
}


void setClickHandler(actionFunc func) {
    funcHighlight = func;
}

BoardManager* ConnectGUI::getBoardManager() const{
    return manager;
}

void ConnectGUI::guiText(){
    btnDrop = new GButton("Enter");
    txtDrop = new GTextField();
    lblWin = new GLabel("");
    txtDrop->setColor("white");
    window->addToRegion(txtDrop, "East");
    window->addToRegion(btnDrop, "East");
    window->addToRegion(lblWin, "East");
    btnDrop->setClickListener([this] {
        manager->dropPiece(stoi(txtDrop->getText()));
        bool test = manager->isWon();
        if (test){
            lblWin->setText("WON");
        }
        redraw();
    });
}
