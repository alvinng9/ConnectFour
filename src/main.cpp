#include "ConnectGUI.h"

ConnectGUI* connectGUI;

void clickHandler(GEvent mouseEvent){
    cout << "test pre click function" << endl;
    int col = mouseEvent.getX() / TILESIZE;
    //int row = mouseEvent.getY() / TILESIZE;
    connectGUI->getBoardManager()->dropPiece(col);
    connectGUI->redraw();
}


int main(){
    connectGUI = new ConnectGUI();
    cout << "test pre setclick Main" << endl;
    //setClickHandler(clickHandler);
    cout << "test post setclick Main" << endl;
    return 0;
}
