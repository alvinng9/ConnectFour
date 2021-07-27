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
    int rowCount = board->getRows();
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
        //pieceDrop = true;
        rowDifference = rowCount - rowHere - 1;
        currentCol = col;
        if (rowDifference > 0){
            pieceDrop = true;
        }
        //board->setPiece(piece,rowHere,col);
        board->setPiece(piece, currentRow, col);
        p1Turn = !p1Turn;
        //sgl::GSound::playSound("woosh.mp3");
    }
}

bool BoardManager::isWon() {
    finishedDropping = false;
    for (int row = 0; row < board->getRows(); row++){
        for (int col = 0; col < board->getCols(); col++){
            if (isWon(0, row, col, 0, 0, " ")){
                return true;
            }
        }
    }
    return false;
}

bool BoardManager::isWon(int sum, int row, int col,int dirVert, int dirHor, string target){
    //base case
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
    outFile << board->getRows() << " " << board->getCols() << " " << p1Turn << endl;
    for (int row = 0; row < board->getRows(); row++){
        for (int col = 0; col < board->getCols(); col++){
            outFile << board->getPiece(row, col) << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

void BoardManager::load(){
    ifstream input;
    input.open("output.txt");
    string piece;
    int rowCount = 0;
    int colCount = 0;
    input >> rowCount;
    input >> colCount;
    input >> p1Turn;
    while (input >> piece){
        for (int row = 0; row < rowCount; row++){
            for (int col = 0; col < colCount; col++){
                board->setPiece(piece, row, col);
            }
        }
    }
    input.close();
}

void BoardManager::resetBoard(){
    p1Turn = true;
    board->resetBoard(board->getRows(),board->getCols());
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
int BoardManager::getRowDifference() const{
    return rowDifference;
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



