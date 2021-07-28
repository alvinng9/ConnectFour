#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;


class Board{
private:
    vector<vector<string>>* boardVector;
public:
    Board(int size);
    string getPiece(int row, int col) const;
    void setPiece(string piece, int row, int col);
    int getSize() const;
    bool inBounds(int row, int col) const;
    void resetBoard(int size);
};

#endif // BOARD_H
