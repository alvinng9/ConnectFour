#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H
#include "Board.h"

class BoardManager {
private:
    Board* board;
public:
    BoardManager(Board* board);
    void dropPiece(int col, string piece);
    bool isWon();
    string winner();
};

#endif // BOARDMANAGER_H
