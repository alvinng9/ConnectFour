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

GButton* btnReset;
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

extern ConnectGUI* connectGUI;

void clickHandler(GEvent mouseEvent);

ConnectGUI::ConnectGUI(){
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
            winnerName = textOne->getText();
        } else {
            winnerName = textTwo->getText();
        }
        if (winnerName == ""){
            winnerName = "An anonymous";
        }
        winnerName += " won!";
        lblWin->setText(winnerName);
        btnReset->setEnabled(true);
        window->removeClickListener();
        redraw();
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
    textOne->setEnabled(setEnable);
    textTwo->setEnabled(setEnable);
}

void ConnectGUI::loadGame(){
    int size;
    int sum;
    manager->load(size, sum);
    sldrNumTile->setValue(size);
    sldrConnectSum->setValue(sum);
    toggle(false);
    window->setClickListener(clickHandler);
    lblWin->setText("");
    btnReset->setEnabled(false);
    redraw();
}

void ConnectGUI::makeMenu(){
    makeSliders();
    /*sldrNumTile->setClickListener([this] {
        cout << "does this work?" << endl;
        manager->resetBoard(sldrNumTile->getValue());
        redraw();
    });*/

    btnColorP1 = makeColorChooser(colorP1);
    btnColorP2 = makeColorChooser(colorP2);

    textOne = playerName("1");
    textTwo = playerName("2");

    btnStartGame = new GButton("Start Game");
    btnStartGame->setClickListener([this] {
        manager->resetBoard(sldrNumTile->getValue());
        manager->setConnectSum(sldrConnectSum->getValue());
        toggle(false);
        window->setClickListener(clickHandler);
        redraw();
    });
    window->addToRegion(btnStartGame, "East");

    lblWin = new GLabel();
    GFont::changeFontSize(lblWin, 20);
    window->addToRegion(lblWin, "South");

    btnReset = new GButton("Reset");
    btnReset->setEnabled(false);
    btnReset->setClickListener([this] {
        btnReset->setEnabled(false);
        lblWin->setText("");
        manager->resetBoard(sldrNumTile->getValue());
        toggle(true);
        redraw();
    });
    window->addToRegion(btnReset, "East");

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
