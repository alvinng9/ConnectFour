#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H
#include "Board.h"
#include <fstream>

class BoardManager {
private:
    Board* board;
    bool p1Turn;
    bool isWon(int sum, int row, int col, int dirVert, int dirRow, string target);
    int rowDifference;
    bool pieceDrop;
    int currentRow;
    int currentCol;
    bool finishedDropping;
    int connectSum;
    int pieceCount;
public:
    BoardManager(Board* board);
    void dropPiece(int col);
    bool isWon();
    void save();
    void load(int& sum);
    void resetBoard(int size);
    bool isP1Turn() const;
    bool isPieceDrop() const;
    int getCurentRow() const;
    int getCurrentCol() const;
    void animate();
    bool isFinishedDropping() const;
    void setConnectSum(int num);
    void reSize(int& size);
    int getPieceCount() const;
};

#endif // BOARDMANAGER_H
