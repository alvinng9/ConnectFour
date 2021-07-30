/**
 * @file ConnectGUI.cpp
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
#include "ConnectGUI.h"
#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
#include "gtextfield.h"
#include "gchooser.h"
#include "gslider.h"
#include "gcolorchooser.h"
#include "gcanvas.h"
#include "gcontainer.h"
#include "gfont.h"

GButton* btnStartGame;
//container for reset and stats buttons
GContainer* panelResetStats;
GButton* btnStats;
GButton* btnReset;
//label for win and turn indicator
GLabel* lblWin;
//color choosers
GCanvas* canvasColorP1;
GCanvas* canvasColorP2;
//text inputs for names
GTextField* textOne;
GTextField* textTwo;
//sliders for win condition and board size
GSlider* sldrConnectSum;
GLabel* lblConnectSumRange;
GSlider* sldrNumTile;
GLabel* lblNumTileRange;
//save and load buttons and container
GContainer* panelSaveLoad;
GButton* btnLoad;
GButton* btnSave;


//names          here or private member variables?
string nameP1;
string nameP2;



extern ConnectGUI* connectGUI;

void clickHandler(GEvent mouseEvent);

ConnectGUI::ConnectGUI(){
    //initialize
    statsGame = {0, 0, 0};
    colorP1 = "red";
    colorP2 = "blue";
    window = new GWindow(550,400, false);
    board = new Board(6);
    manager = new BoardManager(board);
    //window options
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    window->setTitle("Connect Four");
    window->setRegionHorizontalAlignment("east", "center");
    makeMenu();
    window->setTimerListener(80,[this] {
        if (manager->isPieceDrop()){
            lowerPiece();
        } else if (manager->isFinishedDropping()){
            checkWinner();
        }
    });
    window->setVisible(true);
    redraw();
}

void ConnectGUI::lowerPiece(){
    int currentRow = manager->getCurentRow();
    int currentCol = manager->getCurrentCol();
    string piece = board->getPiece(currentRow, currentCol);
    board->setPiece("", currentRow, currentCol);
    board->setPiece(piece,currentRow - 1, currentCol);
    manager->animate();
    window->removeClickListener();
    redraw();
}

void ConnectGUI::checkWinner(){
    window->setClickListener(clickHandler);
    //set winner if won
    if (manager->isWon()){
        bool p1Turn = !manager->isP1Turn();
        string winnerName;
        if (p1Turn){
            statsGame[0]++;
            winnerName = nameP1;
        } else {
            statsGame[1]++;
            winnerName = nameP2;
        }
        redraw();
        winnerName += " Won!";
        lblWin->setText(winnerName);
        btnReset->setEnabled(true);
        window->removeClickListener();
    //manage ties
    } else if (manager->getPieceCount() == pow(board->getSize(),2)){
        statsGame[2]++;
        redraw();
        lblWin->setText("The Game Has Tied");
        btnReset->setEnabled(true);
        window->removeClickListener();
    }
}


void ConnectGUI::redraw(){
    window->clear();
    //draw pieces on board
    for (int i = 0; i < sldrNumTile->getValue(); i++){
        for(int j = 0; j < sldrNumTile->getValue(); j++){
            string pieceHere = board->getPiece(i,j);
            if (pieceHere == ""){
                window->setColor("white");
            } else if (pieceHere == "P1"){
                window->setColor(colorP1);
            } else {
                window->setColor(colorP2);
            }
            window->fillOval(j * TILESIZE + OFFSET, (sldrNumTile->getValue() - i - 1)
                               * TILESIZE + OFFSET, TILESIZE - OFFSET * 2,
                                 TILESIZE - OFFSET * 2);
        }
    }
    //update turn indicator
    if (!btnStartGame->isEnabled()){
        string name;
        if (manager->isP1Turn()){
            name = nameP1;
        } else {
            name = nameP2;
        }
        lblWin->setText(name + "'s turn");
    }
    window->repaint();
}

BoardManager* ConnectGUI::getBoardManager() const{
    return manager;
}

void ConnectGUI::makeSliders(){
    //board size
    GLabel* lblNumTile = new GLabel("Board Size");
    sldrNumTile = new GSlider(5, 7, 6);
    GContainer* panelNumTile = new GContainer();
    GLabel* minNumTile = new GLabel("5");
    GLabel* maxNumTile = new GLabel("7");
    minNumTile->setColor("White");
    maxNumTile->setColor("White");
    panelNumTile->add(minNumTile);
    panelNumTile->add(sldrNumTile);
    panelNumTile->add(maxNumTile);
    lblNumTile->setColor("White");
    window->addToRegion(lblNumTile, "East");
    window->addToRegion(panelNumTile, "East");
    //win condition
    GLabel* lblConnectSum = new GLabel("Consecutive to Win");
    sldrConnectSum = new GSlider(3, 5, 4);
    GContainer* panelConnectSum = new GContainer();
    GLabel* minSum = new GLabel("3");
    GLabel* maxSum = new GLabel("5");
    minSum->setColor("White");
    maxSum->setColor("White");
    panelConnectSum->add(minSum);
    panelConnectSum->add(sldrConnectSum);
    panelConnectSum->add(maxSum);
    lblConnectSum->setColor("White");
    window->addToRegion(lblConnectSum, "East");
    window->addToRegion(panelConnectSum, "East");
}

GCanvas* ConnectGUI::makeColorChooser(string& color){
    GCanvas* colorPreview = new GCanvas(20, 20, color);
    colorPreview->setClickListener([colorPreview, &color] {
        color = GColorChooser::showDialog("Choose a color");
        colorPreview->setBackground(color);
    });
    GContainer* panelColor = new GContainer();
    GLabel* lblColor = new GLabel("Choose a color: ");
    lblColor->setColor("White");
    panelColor->add(lblColor);
    panelColor->add(colorPreview);
    window->addToRegion(panelColor, "East");
    return colorPreview;
}

GTextField* ConnectGUI::playerName(string player){
    GLabel* lblPlayer = new GLabel("Name of Player " + player);
    lblPlayer->setColor("White");
    GTextField* textPlayer = new GTextField("Player " + player, 10);
    window->addToRegion(lblPlayer, "East");
    window->addToRegion(textPlayer, "East");
    return textPlayer;
}

void ConnectGUI::toggle(bool setEnable){
    //color preview canvases
    if (setEnable) {
        canvasColorP1->setClickListener([this] {
            colorP1 = GColorChooser::showDialog("Choose a color");
            canvasColorP1->setBackground(colorP1);
        });
            canvasColorP2->setClickListener([this] {
            colorP2 = GColorChooser::showDialog("Choose a color");
            canvasColorP2->setBackground(colorP2);
        });
    } else {
        canvasColorP1->removeClickListener();
        canvasColorP2->removeClickListener();
    }
    //other menu interactors
    sldrConnectSum->setEnabled(setEnable);
    sldrNumTile->setEnabled(setEnable);
    btnStartGame->setEnabled(setEnable);
    textOne->setEnabled(false);
    textTwo->setEnabled(false);
}

void ConnectGUI::loadGame(){
    int size;
    int sum;
    manager->reSize(size);
    sldrNumTile->setValue(size);
    manager->load(sum);
    sldrConnectSum->setValue(sum);
    toggle(false);
    window->setClickListener(clickHandler);
    lblWin->setText("");
    btnReset->setEnabled(false);
    redraw();
}

void ConnectGUI::startGame() {
    nameP1 = textOne->getText();
    nameP2 = textTwo->getText();
    string name;
    if (nameP1 == "" && nameP2 == "") {
        nameP1 = "An Anonymous";
        nameP2 = "The Other Anonymous";
    } else if (nameP1 == "") {
        nameP1 = "An Anonymous";
    } else if (nameP2 == ""){
        nameP2 = "An Anonymous";
    }
    manager->setConnectSum(sldrConnectSum->getValue());
    toggle(false);
    window->setClickListener(clickHandler);
    redraw();
}

void ConnectGUI::showStats() {
    //initialize
    GWindow* popUpWindow = new GWindow(250,100);
    popUpWindow->setLocation(450, 300);
    popUpWindow->setBackground("black");
    popUpWindow->setExitOnClose(false);
    popUpWindow->setAutoRepaint(false);
    popUpWindow->setTitle("Statistics");
    popUpWindow->setColor("White");
    //write stats
    string statsP1 = textOne->getText() + " has won " + to_string(statsGame[0]) + " time(s)";
    popUpWindow->drawString(statsP1, 20, 21);
    string statsP2 = textTwo->getText() + " has won " + to_string(statsGame[1]) + " time(s)";
    popUpWindow->drawString(statsP2, 20, 41);
    string statsDraw = "There has/have been " + to_string(statsGame[2]) + " tie(s)";
    popUpWindow->drawString(statsDraw, 20, 61);
    //close button
    GButton* btnClose = new GButton("Close");
    btnClose->setClickListener([popUpWindow] {
        popUpWindow->close();
    });
    popUpWindow->addToRegion(btnClose, "South");
}

void ConnectGUI::makeMenu(){
    //sliders
    makeSliders();
    sldrNumTile->setActionListener([this] {
        manager->resetBoard(sldrNumTile->getValue());
        redraw();
    });
    //color choosers
    canvasColorP1 = makeColorChooser(colorP1);
    canvasColorP2 = makeColorChooser(colorP2);
    //name setters
    textOne = playerName("1");
    textTwo = playerName("2");
    //start game button
    btnStartGame = new GButton("Start Game");
    btnStartGame->setClickListener([this] {
        startGame();
    });
    window->addToRegion(btnStartGame, "East");
    //winner and turn label
    lblWin = new GLabel("Press 'Start Game' to Begin");
    lblWin->setColor("White");
    GFont::changeFontSize(lblWin, 20);
    window->addToRegion(lblWin, "South");
    //reset button
    panelResetStats = new GContainer;
    btnReset = new GButton("Reset");
    btnReset->setEnabled(false);
    btnReset->setClickListener([this] {
        btnReset->setEnabled(false);
        lblWin->setText("");
        manager->resetBoard(sldrNumTile->getValue());
        toggle(true);
        redraw();
    });
    //stats button
    btnStats = new GButton("Statistics");
    btnStats->setClickListener([this] {
        showStats();
    });
    panelResetStats->add(btnReset);
    panelResetStats->add(btnStats);
    window->addToRegion(panelResetStats, "East");
    //load button
    panelSaveLoad = new GContainer();
    btnLoad = new GButton("Load");
    btnLoad->setClickListener([this] {
        loadGame();
    });
    //save button
    btnSave = new GButton("Save");
    btnSave->setClickListener([this] {
        manager->save();
    });
    panelSaveLoad->add(btnLoad);
    panelSaveLoad->add(btnSave);
    window->addToRegion(panelSaveLoad, "East");
}

void clickHandler(GEvent mouseEvent){
    int col = mouseEvent.getX() / TILESIZE;
    int row = mouseEvent.getY() / TILESIZE;
    if (col < sldrNumTile->getValue() && row < sldrNumTile->getValue()) {
        connectGUI->getBoardManager()->dropPiece(col);
        connectGUI->redraw();
    }
}


