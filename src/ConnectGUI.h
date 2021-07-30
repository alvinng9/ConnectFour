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
#include <vector>
#include "BoardManager.h"
#include "gwindow.h"
#include "gbutton.h"
#include "gtextfield.h"
#include "gslider.h"
#include "glabel.h"


using namespace sgl;

//board dimensions and animation speed
int static TILESIZE = 50;
int static OFFSET = 5;
int static ANIMATION_INTERVAL = 80;
//window size and location
int static WINDOW_WIDTH = 550;
int static WINDOW_HEIGHT = 400;
int static WINDOW_LOCATION_X = 300;
int static WINDOW_LOCATION_Y = 100;
//stats window size
int static STATS_WIDTH = 280;
int static STATS_HEIGHT = 100;
int static STATS_LOCATION_X = 450;
int static STATS_LOCATION_Y = 300;

class ConnectGUI{
private:
    BoardManager* manager;
    Board* board;
    GWindow* window;
    //piece colors
    string colorP1;
    string colorP2;
    //player names
    string nameP1;
    string nameP2;
    //count of p1 wins, p2 wins, and ties
    vector<int> statsGame;
    //slider for win condition
    GSlider* sldrConnectSum;
    //start, reset, and stats buttons
    GButton* btnStartGame;
    GButton* btnReset;
    GButton* btnStats;
    //label for win and turn indicator
    GLabel* lblWin;
    //color chooser canvases
    GCanvas* canvasColorP1;
    GCanvas* canvasColorP2;
    //text inputs for names
    GTextField* textOne;
    GTextField* textTwo;

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
     * @return a GCanvas* that allows the user to select a color
     */
    GCanvas* makeColorChooser(string& color);

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

    /**
     * @brief Save the names from text fields
     *
     */
    void getNames();

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
