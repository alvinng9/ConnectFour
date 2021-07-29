/**
 * @file Board.cpp
 * @author Alvin Nguyen (https://github.com/alvinng9)
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class represents a Connect Four board. It has several functions to
 * modify and read the board state.
 * @version 0.1
 * @date 2021-07-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Board.h"

Board::Board(int size){
    if (size == 0){
        throw "bad";
    } else {
        boardVector = nullptr;
        resetBoard(size);
    }
}

void Board::resetBoard(int size){
    if (boardVector != nullptr){
        delete boardVector;
    }
    boardVector = new vector<vector<string>>;
    for (int i = 0; i < size; i++){
        vector<string> rowVector;
        for (int j = 0; j < size; j++){
            rowVector.push_back("");
        }
        boardVector->push_back(rowVector);
    }
}

string Board::getPiece(int row, int col) const{
    return (*boardVector)[row][col];
}

void Board::setPiece(string piece, int row, int col){
    (*boardVector)[row][col] = piece;
}

int Board::getSize() const{
    return boardVector->size();
}


bool Board::inBounds(int row, int col) const{
    return (row >= 0 && row < getSize() && col >= 0 && col < getSize());
}

