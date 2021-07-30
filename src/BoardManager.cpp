/**
 * @file BoardManager.cpp
 * @author Alvin Nguyen (https://github.com/alvinng9)
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class handles running the Connect Four game by keeping track
 * of the game state and passing information between the GUI and board.
 * @version 0.1
 * @date 2021-07-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "BoardManager.h"
#include "gsound.h"

BoardManager::BoardManager(Board* board){
    this->board = board;
    p1Turn = true;
    connectSum = 4;
    finishedDropping = false;
    pieceDrop = false;
    pieceCount = 0;
}

void BoardManager::dropPiece(int col){
    string pieceHere = board->getPiece(0,col);
    int rowHere = 0;
    int rowCount = board->getSize();
    //find which row to place the piece at
    while (pieceHere != "" && rowHere < rowCount - 1){
        rowHere++;
        pieceHere = board->getPiece(rowHere,col);
    }
    //drop a piece if location was in bounds
    if (rowHere < rowCount && pieceHere == ""){
        pieceCount++;
        string piece = "";
        if (p1Turn){
            piece = "P1";
        } else {
            piece = "P2";
        }
        currentRow = rowCount - 1;
        rowDifference = rowCount - rowHere - 1;
        currentCol = col;
        board->setPiece(piece, currentRow, col);
        //set a flag for starting the drop animation if not dropping at top
        if (rowDifference > 0){
            pieceDrop = true;
        } else {
            finishedDropping = true;
        }
        p1Turn = !p1Turn;
        sgl::GSound::playSound("wooshh.mp3");
    }
}

bool BoardManager::isWon() {
    finishedDropping = false;
    for (int row = 0; row < board->getSize(); row++){
        for (int col = 0; col < board->getSize(); col++){
            if (isWon(0, row, col, 0, 0, " ")){
                return true;
            }
        }
    }
    return false;
}

bool BoardManager::isWon(int sum, int row, int col,int dirVert, int dirHor, string target){
    //base cases
    if (sum == connectSum){
        return true;
    }
    if (!board->inBounds(row, col)){
        return false;
    }
    string player = board->getPiece(row, col);
    if (player == "") {
        return false;
    }
    //initial case for checking each direction, no direction currently locked
    if (dirVert == dirHor && dirVert == 0) {
        bool n = isWon(sum, row, col, -1, 0, player); //North
        bool s = isWon(sum, row, col, 1, 0, player); //South
        bool w = isWon(sum, row, col, 0, -1, player); //West
        bool e = isWon(sum, row, col, 0, 1, player); //East
        bool nw = isWon(sum, row, col, -1, -1, player); //Northwest
        bool ne = isWon(sum, row, col, -1, 1, player); //Northeast
        bool sw = isWon(sum, row, col, 1, -1, player); //Southwest
        bool se = isWon(sum, row, col, 1, 1, player); //Southeast
        return (n || s || w || e || nw || ne || sw || se);
    //check if the next piece in the locked direction belongs to the same player
    } else {
        if (player == target){
            return isWon(sum + 1, row + dirVert, col + dirHor, dirVert, dirHor, target);
        } else {
            return false;
        }
    }
}

void BoardManager::save(){
    ofstream outFile;
    outFile.open ("output.txt");
    outFile << board->getSize() << " " << p1Turn << " " << connectSum << " " << pieceCount <<  endl;
    for (int row = 0; row < board->getSize(); row++){
        for (int col = 0; col < board->getSize(); col++){
            string piece = board->getPiece(row, col);
            if (piece == ""){
                outFile << "P0" << " ";
            } else {
                outFile << piece << " ";
            }
        }
        outFile << endl;
    }
    outFile.close();
}

void BoardManager::load(int& sum){
    ifstream input;
    input.open("output.txt");
    string piece;
    int size;
    input >> size;
    input >> p1Turn;
    input >> connectSum;
    input >> pieceCount;
    sum = connectSum;
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++){
            input >> piece;
            if (piece == "P0"){
                piece = "";
            }
            board->setPiece(piece, row, col);
        }
    }
    input.close();
}

void BoardManager::reSize(int& size){
    ifstream input;
    input.open("output.txt");
    input >> size;
    resetBoard(size);
    input.close();
}

void BoardManager::resetBoard(int size){
    pieceCount = 0;
    p1Turn = true;
    board->resetBoard(size);
}

bool BoardManager::isP1Turn() const{
    return p1Turn;
}

bool BoardManager::isPieceDrop() const{
    return pieceDrop;
}
int BoardManager::getCurentRow() const{
    return currentRow;
}
int BoardManager::getCurrentCol() const {
    return currentCol;
}

void BoardManager::animate(){
    currentRow--;
    rowDifference--;
    if (rowDifference == 0) {
        pieceDrop = false;
        finishedDropping = true;
    }
}

bool BoardManager::isFinishedDropping() const{
    return finishedDropping;
}

void BoardManager::setConnectSum(int num) {
    this->connectSum = num;
}

int BoardManager::getPieceCount() const{
    return pieceCount;
}
