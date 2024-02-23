//
// Created by Caleb Rutledge on 2/21/24.
//

#include <iostream>
#include "Game.h"

int main( int argc, char* args[] ) {
    std::cout << args[1];
    std::string scenePath = "Assets/Scenes/";
    scenePath += args[1];
    Game game{scenePath};
    game.run();
}