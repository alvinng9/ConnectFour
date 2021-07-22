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
    Board(int row, int col);
    string getPiece(int row, int col) const;
    void setPiece(string piece, int row, int col);
    int getRows() const;
    int getCols() const;
};

#endif // BOARD_H
