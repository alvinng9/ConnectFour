#include "ConnectGUI.h"

ConnectGUI::ConnectGUI(){
    window = new GWindow(300,300);
    board = new Board(6,6);
    manager = new BoardManager(board);
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    window->setTitle("Connect Four");
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
            window->fillOval(j * TILESIZE + OFFSET,i * TILESIZE + OFFSET, TILESIZE - OFFSET * 2, TILESIZE - OFFSET * 2);
        }
    }
    window->repaint();
}

void ConnectGUI::clickHandler(){

}
