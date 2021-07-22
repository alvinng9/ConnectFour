#include "Board.h"

Board::Board(int row, int col){
    if (row == 0 || col == 0){
        throw "bad";
    } else {
        boardVector = new vector<vector<string>>;
        for (int i = 0; i < row; i++){
            vector<string> rowVector;
            for (int j = 0; j < col; j++){
                rowVector.push_back("");
            }
            boardVector->push_back(rowVector);
        }
    }
}

string Board::getPiece(int row, int col) const{
    return (*boardVector)[row][col];
}

void Board::setPiece(string piece, int row, int col){
    (*boardVector)[row][col] = piece;
}

int Board::getRows() const{
    return boardVector->size();
}

int Board::getCols() const{
    return boardVector[0].size();
}

