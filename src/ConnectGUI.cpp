#include "ConnectGUI.h"
#include <iomanip>
#include "gthread.h"
#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
#include "gobjects.h"
#include "gradiobutton.h"
#include "gtextfield.h"
#include "gchooser.h"
#include "gslider.h"

GButton* btnReset;
GLabel* lblWin;
GLabel* playerOne;
GLabel* playerTwo;
GTextField* textOne;
GTextField* textTwo;
GButton* btnStartGame;
GChooser* dropDown;
GSlider* slider;
GLabel* lblSlider;

extern ConnectGUI* connectGUI;

void clickHandler(GEvent mouseEvent);

ConnectGUI::ConnectGUI(){
    window = new GWindow(450,400);
    board = new Board(6,6);
    manager = new BoardManager(board);
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    window->setTitle("Connect Four");
    makeMenu();
    window->setTimerListener(80,[this] {
        if (manager->isPieceDrop()){
            int currentRow = manager->getCurentRow();
            int currentCol = manager->getCurrentCol();
            string piece = board->getPiece(currentRow, currentCol);
            board->setPiece("", currentRow, currentCol);
            board->setPiece(piece,currentRow - 1, currentCol);
            manager->animate();
            window->removeClickListener();
            redraw();
        } else if (manager->isFinishedDropping()){
            window->setClickListener(clickHandler);
            if (manager->isWon()){
                bool p1Turn = !manager->isP1Turn();
                string winnerName;
                if (p1Turn){
                    winnerName = textOne->getText();
                } else {
                    winnerName = textTwo->getText();
                }
                if (winnerName == ""){
                    winnerName = "An anonymous";
                }
                winnerName += " won!";
                lblWin->setText(winnerName);
                btnReset->setEnabled(true);
                window->removeClickListener();
                redraw();
            }
        }
    });
    redraw();
}

GWindow* ConnectGUI::getWindow() const{
    return window;
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

BoardManager* ConnectGUI::getBoardManager() const{
    return manager;
}

void ConnectGUI::makeMenu(){
    slider = new GSlider(3,5,4);
    //window->addToRegion(slider, "East");
    lblSlider = new GLabel("  3      4      5");
    window->addToRegion(lblSlider, "East");
    window->addToRegion(slider, "East");
    //dropDown = new GChooser(CONNECTCOUNT);
    //window->addToRegion(dropDown, "East");
    playerOne = new GLabel("Name of player one: ");
    playerTwo = new GLabel("Name of player two: ");
    textOne = new GTextField("Player 1", 10);
    textTwo = new GTextField("Player 2", 10);
    btnStartGame = new GButton("Start Game");
    btnStartGame->setClickListener([this] {
        //dropDown->setEnabled(false);
        int connectHere = slider->getValue();
        slider->setEnabled(false);
        manager->setConnectSum(connectHere);
        btnStartGame->setEnabled(false);
        textOne->setEnabled(false);
        textTwo->setEnabled(false);
        window->setClickListener(clickHandler);
    });
    window->addToRegion(playerOne, "East");
    window->addToRegion(textOne, "East");
    window->addToRegion(playerTwo, "East");
    window->addToRegion(textTwo, "East");
    window->addToRegion(btnStartGame, "East");

    lblWin = new GLabel();
    window->addToRegion(lblWin, "East");
    btnReset = new GButton("Reset");
    btnReset->setEnabled(false);
    btnReset->setClickListener([this] {
        btnReset->setEnabled(false);
        connectGUI->getBoardManager()->resetBoard();
        lblWin->setText("");
        //dropDown->setEnabled(true);
        slider->setEnabled(true);
        textOne->setEnabled(true);
        textTwo->setEnabled(true);
        btnStartGame->setEnabled(true);
        redraw();
    });
    window->addToRegion(btnReset, "East");
}

void clickHandler(GEvent mouseEvent){
    int col = mouseEvent.getX() / TILESIZE;
    connectGUI->getBoardManager()->dropPiece(col);
    connectGUI->redraw();
}
