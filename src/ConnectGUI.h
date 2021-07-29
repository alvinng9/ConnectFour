/**
 * @file ConnectGUI.h
 * @author Alvin Nguyen (https://github.com/alvinng9)
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class creates a window for the user to play a game of Connect 
 * Four against another player. The player can customize the game using the
 * options menu displayed on the right.
 * @version 0.1
 * @date 2021-07-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CONNECTGUI_H
#define CONNECTGUI_H
#include "BoardManager.h"
#include "gwindow.h"
#include <vector>
#include "gbutton.h"
#include "gtextfield.h"


using namespace sgl;

int static TILESIZE = 50;
int static OFFSET = 5;

class ConnectGUI{
private:
    BoardManager* manager;
    Board* board;
    GWindow* window;
    string colorP1;
    string colorP2;
    vector<int> statsGame;

    /**
     * @brief Creates all GUI items for the menu on the right side.
     * 
     */
    void makeMenu();

    /**
     * @brief Creates the sliders for choosing the win condition and board size.
     * 
     */
    void makeSliders();

    /**
     * @brief Creates the elements for allowing the user to pick their piece colors.
     * 
     * @param color the string that stores the color of the player's piece
     * @return a GButton* that allows the user to select a color
     */
    GButton* makeColorChooser(string& color);

    /**
     * @brief Creates the elements for allowing the user to change their names.
     * 
     * @param player the first or second player's name
     * @return a GTextField* that allows the user to input their name
     */
    GTextField* playerName(string player);

    /**
     * @brief Toggles all game customization buttons/sliders/textfields.
     * 
     * @param setEnable whether the elements should be enabled(true)
     */
    void toggle(bool setEnable);

    /**
     * @brief Updates the board and sliders to reflect the state saved in
     * "output.txt"
     * 
     */
    void loadGame();

    /**
     * @brief Begins the game and locks out user customization menus.
     * 
     */
    void startGame();

    /**
     * @brief Creates a new window that displays game statistics.
     * 
     */
    void showStats();

    /**
     * @brief Lowers the currently dropping piece by one row.
     * @pre there is a piece currently dropping
     * 
     */
    void lowerPiece();

    /**
     * @brief Checks if someone has won the game and reports the winner
     * on screen.
     * 
     */
    void checkWinner();
public:
    /**
     * @brief Constructs a ConnectGUI object.
     * 
     */
    ConnectGUI();

    /**
     * @brief Redraws the board after clearing previously drawn board state.
     * 
     */
    void redraw();

    /**
     * @brief Returns a pointer to the manager currently running the game.
     * 
     * @return the BoardManager* currently running the game.
     */
    BoardManager* getBoardManager() const;
};


#endif // CONNECTGUI_H
