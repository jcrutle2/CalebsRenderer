/*
 * MAIN FILE
 * Created 12/31/23
 */


#include "Editor.h"

int main( int argc, char* args[] ) {
    Editor mainGame;

    if(strcmp(args[1], "none") != 0) {
        mainGame.loadScene(args[1]);
    }

    mainGame.run();
}