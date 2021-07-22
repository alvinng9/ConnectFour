#include "BoardManager.h"

BoardManager::BoardManager(Board* board){
    this->board = board;
}

void BoardManager::dropPiece(int col, string piece){
    string pieceHere = board->getPiece(0,col);
    int rowHere = 0;
    int rowCount = board->getRows();
    while (pieceHere != "" && rowHere < rowCount){
        rowHere++;
        pieceHere = board->getPiece(rowHere,col);
    }
    if (rowHere != rowCount){
        board->setPiece(piece,rowHere,col);
    }
}

bool BoardManager::isWon(){
    //base case
    //check case
        //choose
        //explore
        //unchoose
    return true;
}

string BoardManager::winner(){
    return "test";
}
