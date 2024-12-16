/* 
 * File:   Game.h
 * Author: Adam Zavala
 *
 * Created on November 29, 2024, 12:34 PM
 */

#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include <fstream>

class Game{
    private:
        Player *player;
        Dealer *dealer;
        Deck *deck;
        fstream data;
        bool stand, bust, blackjack, ins;
        void initializeHand();
        void playHand();
        template <typename T> T validateBet();
        char validateInput(string);
        void playerActions();
        void playerHandInput();
        void playerConfirmation();
        void dealerActions();
        void winConditions();
        void loadProfile();
        void newProfile();
        string errorCode(int);
    public:
        Game();
        ~Game();
        void playGame();
        void loadGame();
        void saveGame();
};

#endif /* GAME_H */