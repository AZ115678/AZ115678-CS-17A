/* 
 * File:   Game.h
 * Author: buddy
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
        bool stand, bust, blackjack;
        void initializeHand();
        void playHand();
        void playerActions();
        void dealerActions();
    public:
        Game();
        ~Game();
        void playGame();
        void loadGame();
        void saveGame();
};

#endif /* GAME_H */

