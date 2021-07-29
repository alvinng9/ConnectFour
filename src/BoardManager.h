/**
 * @file BoardManager.h
 * @author Alvin Nguyen (https://github.com/alvinng9)
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class handles running the Connect Four game by keeping track
 * of the game state and passing information between the GUI and board.
 * @version 0.1
 * @date 2021-07-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H
#include "Board.h"
#include <fstream>
#include <tgmath.h> 

class BoardManager {
private:
    Board* board;
    bool p1Turn;
    //
    int rowDifference;
    bool pieceDrop;
    int currentRow;
    int currentCol;
    bool finishedDropping;
    int connectSum;
    int pieceCount;

    /**
     * @brief Checks if a player has won the game by making a chain of pieces
     * of 3-5 as specified in options.
     * 
     * @param sum the current chain length
     * @param row the current row
     * @param col the current column
     * @param dirVert the vertical direction
     * @param dirRow the horizontal direction
     * @param target the target chain length to win
     * @return true if the chain length is equal to the target length
     * @return false if no chain reaches the target length
     */
    bool isWon(int sum, int row, int col, int dirVert, int dirRow, string target);

public:
    /**
     * @brief Constructs a BoardManger that will manage a game on the passed
     * in board.
     * 
     * @param board the board to play on
     */
    BoardManager(Board* board);

    /**
     * @brief Tries to place a piece at the specified column.
     * 
     * @param col the column to drop the piece down
     */
    void dropPiece(int col);

    /**
     * @brief Checks if a player has won the game.
     * 
     * @return true if someone has won
     * @return false if there is no winner yet
     */
    bool isWon();

    /**
     * @brief Saves the board state to the file "output.txt".
     * 
     */
    void save();

    /**
     * @brief Loads the board state from the file "output.txt" and modifies the
     * passed-in integer to store the number of pieces in a chain required to win.
     * @pre "output.txt" exists
     * 
     * @param sum the number of pieces in a chain to win
     */
    void load(int& sum);

    /**
     * @brief Resizes the board according to "output.txt" and modifies the
     * passed-in integer to store the number of rows and columns of the board.
     * 
     * @param size the number of rows and columns of the board
     */
    void reSize(int& size);

    /**
     * @brief Sets the board to an empty board of the passed-in number of
     * rows and columns.
     * 
     * @param size the number of rows and columns
     */
    void resetBoard(int size);

    /**
     * @brief Returns whether it is currently the first player's turn.
     * 
     * @return true if it is the first player's turn
     * @return false if it is second player's turn
     */
    bool isP1Turn() const;

    /**
     * @brief Returns whether there is a piece in its dropping animation.
     * 
     * @return true if a piece is currently dropping
     * @return false if no piece is currently dropping
     */
    bool isPieceDrop() const;

    /**
     * @brief Returns the row of any currently dropping piece.
     * @pre A piece is actually dropping currently
     * 
     * @return int the row of the currently dropping piece
     */
    int getCurentRow() const;

    /**
     * @brief Returns the column of any currently dropping piece.
     * @pre A piece is actually dropping currently
     * 
     * @return int the column of the currently dropping piece
     */
    int getCurrentCol() const;

    /**
     * @brief Increments the current row location of a dropping piece and the
     * number of rows the piece has left to drop. If the piece has reached
     * its destination, sets finishedDropping to true.
     * @pre A piece is actually dropping currently
     * 
     */
    void animate();

    /**
     * @brief Returns whether a piece has freshly finished dropping.
     * 
     * @return true if the piece has just finished dropping
     * @return false if no piece has just dropped
     */
    bool isFinishedDropping() const;

    /**
     * @brief Set the piece chain length win condition.
     * 
     * @param num the number of pieces in chain required to win
     */
    void setConnectSum(int num);

    /**
     * @brief Returns the number of pieces currently placed in the board.
     * 
     * @return int the number of pieces
     */
    int getPieceCount() const;
};

#endif // BOARDMANAGER_H
