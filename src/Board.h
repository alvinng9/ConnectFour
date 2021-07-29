/**
 * @file Board.h
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
    /**
     * @brief Constructs a Connect Four board.
     * 
     * @param size the number of rows and columns in the board
     */
    Board(int size);

    /**
     * @brief Returns the piece at the passed location.
     * 
     * @param row the row of the location
     * @param col the column of the location
     * @return a string representing the piece's owner
     */
    string getPiece(int row, int col) const;

    /**
     * @brief Sets the owner of the piece at the passed location.
     * 
     * @param piece a string representing the piece's owner
     * @param row the row to place the piece
     * @param col the column to place the piece
     */
    void setPiece(string piece, int row, int col);

    /**
     * @brief Gets the number of rows and columns of the board.
     * 
     * @return the number of rows/columns
     */
    int getSize() const;

    /**
     * @brief Checks if the passed location is within the board.
     * 
     * @param row the row to check
     * @param col the column to check
     * @return true if a valid location on the board
     * @return false if out of bounds
     */
    bool inBounds(int row, int col) const;

    /**
     * @brief Sets the board to be empty with the specified size.
     * 
     * @param size the nubmer of rows and columns for the board
     */
    void resetBoard(int size);
};

#endif // BOARD_H
