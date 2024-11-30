/* 
 * File:   Player.h
 * Author: Adam Zavala
 * Purpose: Structure to hold player and dealer information
 * Created on November 4, 2024, 12:11 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Dealer.h"
#include "Cards.h"
//#include "Deck.h"
#include <vector>

using namespace std;

class Player : public Dealer{
    private:
        float cash, bet;
        
    public:
        Player();
        Player(string);
        ~Player();
        void setBet(float);
        void doubleBet();
        void winBet(bool);
        void loseBet();
        void pushBet();
        void setCash(int c){cash = c;}
        float getCash(){return cash;}
        float getBet(){return bet;}
};

#endif /* PLAYER_H */

