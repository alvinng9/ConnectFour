#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H
#include "Board.h"
#include <fstream>

class BoardManager {
private:
    Board* board;
    bool p1Turn;
    bool isWon(int sum, int row, int col, int dirVert, int dirRow, string target);
public:
    BoardManager(Board* board);
    void dropPiece(int col);
    bool isWon();
    string winner();
    void save();
    void load();
};

#endif // BOARDMANAGER_H
