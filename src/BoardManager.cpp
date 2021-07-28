#include "BoardManager.h"
#include "gsound.h"

BoardManager::BoardManager(Board* board){
    this->board = board;
    p1Turn = true;
    connectSum = 4;
    finishedDropping = false;
    pieceDrop = false;
}

void BoardManager::dropPiece(int col){
    string pieceHere = board->getPiece(0,col);
    int rowHere = 0;
    int rowCount = board->getSize();
    while (pieceHere != "" && rowHere < rowCount - 1){
        rowHere++;
        pieceHere = board->getPiece(rowHere,col);
    }
    if (rowHere < rowCount && pieceHere == ""){
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
        if (rowDifference > 0){
            pieceDrop = true;
        } else {
            finishedDropping = true;
        }
        p1Turn = !p1Turn;
        //sgl::GSound::playSound("woosh.mp3");
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
    if (!board->inBounds(row, col)){
        return false;
    }

    string player = board->getPiece(row, col);
    if (sum == connectSum){
        return true;
    } else if (player == "") {
        return false;
    }

    // comments here to be neater
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
    outFile << board->getSize() << " " << p1Turn << " " << connectSum << " " <<  endl;
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

void BoardManager::load(int& size, int& sum){
    ifstream input;
    input.open("output.txt");
    string piece;
    input >> size;
    input >> p1Turn;
    input >> connectSum;
    sum = connectSum;
    board->resetBoard(size);
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

void BoardManager::resetBoard(int size){
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



