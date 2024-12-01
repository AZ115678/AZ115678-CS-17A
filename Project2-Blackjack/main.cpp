/* 
 * File:   main.cpp
 * Author: Adam Zavala
 * Purpose: Project 2 - Simple Blackjack that displays concepts learned from chapters 13-16
 * Created on October 17, 2024, 12:13 PM
 */

#include <iostream>
#include <cstdlib>

using namespace std;

#include "Game.h"

int main(int argc, char** argv) {
    //new game object 
    Game game;
    //load player cash from last game
    game.loadGame();
    cout << "Welcome to the Blackjack table! \n" << endl;
    //gameplay loop
    game.playGame();
    //saves player cash for next time
    game.saveGame();
    return 0;
}