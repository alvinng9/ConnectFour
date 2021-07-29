#include "ConnectGUI.h"
#include <iomanip>
#include "gthread.h"
#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
#include "gobjects.h"
#include "gradiobutton.h"
#include "gtextfield.h"
#include "gchooser.h"
#include "gslider.h"
#include "gcolorchooser.h"
#include "gcanvas.h"
#include "gcontainer.h"
#include "gfont.h"

GContainer* panelResetStats;
GButton* btnStats;
GButton* btnReset;
GButton* btnClose;
GLabel* lblWin;
GTextField* textOne;
GTextField* textTwo;
GButton* btnStartGame;
GSlider* sldrConnectSum;
GLabel* lblConnectSumRange;
GSlider* sldrNumTile;
GLabel* lblNumTileRange;
GColorChooser* colorChoose;
GButton* btnColorP1;
GButton* btnColorP2;
GButton* btnLoad;
GButton* btnSave;
GContainer* panelSaveLoad;
string nameP1;
string nameP2;



extern ConnectGUI* connectGUI;

void clickHandler(GEvent mouseEvent);

ConnectGUI::ConnectGUI(){
    statsGame = {0, 0, 0};
    colorP1 = "red";
    colorP2 = "blue";
    window = new GWindow(550,400);
    board = new Board(6);
    manager = new BoardManager(board);
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    window->setTitle("Connect Four");
    makeMenu();
    window->setTimerListener(80,[this] {
        if (manager->isPieceDrop()){
            lowerPiece();
        } else if (manager->isFinishedDropping()){
            checkWinner();
        }
    });
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
    GLabel* lblNumTile = new GLabel("Board Size");
    sldrNumTile = new GSlider(5, 7, 6);
    lblNumTileRange = new GLabel("  5      6      7");
    window->addToRegion(lblNumTile, "East");
    window->addToRegion(lblNumTileRange, "East");
    window->addToRegion(sldrNumTile, "East");

    GLabel* lblConnectSum = new GLabel("Consecutive to Win");
    sldrConnectSum = new GSlider(3, 5, 4);
    lblConnectSumRange = new GLabel("  3      4      5");
    window->addToRegion(lblConnectSum, "East");
    window->addToRegion(lblConnectSumRange, "East");
    window->addToRegion(sldrConnectSum, "East");
}

GButton* ConnectGUI::makeColorChooser(string& color){
    GCanvas* colorPreview = new GCanvas(20, 20, color);
    GContainer* panelColor = new GContainer();
    GButton* btnColor = new GButton("Color for Player 1");
    btnColor->setClickListener([colorPreview, &color] {
        color = GColorChooser::showDialog("Choose a color");
        colorPreview->setBackground(color);
    });
    panelColor->add(btnColor);
    panelColor->add(colorPreview);
    window->addToRegion(panelColor, "East");
    return btnColor;
}

GTextField* ConnectGUI::playerName(string player){
    GLabel* lblPlayer= new GLabel("Name of Player " + player);
    GTextField* textPlayer = new GTextField("Player " + player, 10);
    window->addToRegion(lblPlayer, "East");
    window->addToRegion(textPlayer, "East");
    return textPlayer;
}

void ConnectGUI::toggle(bool setEnable){
    btnColorP1->setEnabled(setEnable);
    btnColorP2->setEnabled(setEnable);
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

void ConnectGUI::makeMenu(){
    makeSliders();

    sldrNumTile->setActionListener([this] {
        manager->resetBoard(sldrNumTile->getValue());
        redraw();
    });

    btnColorP1 = makeColorChooser(colorP1);
    btnColorP2 = makeColorChooser(colorP2);

    textOne = playerName("1");
    textTwo = playerName("2");

    btnStartGame = new GButton("Start Game");
    btnStartGame->setClickListener([this] {
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
    });
    window->addToRegion(btnStartGame, "East");

    lblWin = new GLabel("Press 'Start Game' to Begin");
    GFont::changeFontSize(lblWin, 20);
    window->addToRegion(lblWin, "South");

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

    btnStats = new GButton("Statistics");
    btnStats->setClickListener([this] {
        GWindow* popUpWindow = new GWindow(250,100);
        popUpWindow->setLocation(450, 300);
        popUpWindow->setBackground("black");
        popUpWindow->setExitOnClose(false);
        popUpWindow->setAutoRepaint(false);
        popUpWindow->setTitle("Statistics");
        string statsP1 = textOne->getText() + " has won " + to_string(statsGame[0]) + " time(s)";
        popUpWindow->drawString(statsP1, 20, 21);
        string statsP2 = textTwo->getText() + " has won " + to_string(statsGame[1]) + " time(s)";
        popUpWindow->drawString(statsP2, 20, 41);
        string statsDraw = "There has/have been " + to_string(statsGame[2]) + " tie(s)";
        popUpWindow->drawString(statsDraw, 20, 61);

        btnClose = new GButton("Close");
        btnClose->setClickListener([popUpWindow] {
            popUpWindow->close();
        });
        popUpWindow->addToRegion(btnClose, "South");
    });

    panelResetStats->add(btnReset);
    panelResetStats->add(btnStats);
    window->addToRegion(panelResetStats, "East");

    panelSaveLoad = new GContainer();
    btnLoad = new GButton("Load");
    btnLoad->setClickListener([this] {
        loadGame();
    });

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
    connectGUI->getBoardManager()->dropPiece(col);
    connectGUI->redraw();
}


