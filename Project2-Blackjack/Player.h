/* 
 * File:   Player.h
 * Author: Adam Zavala
 * Purpose: Structure to hold player and dealer information
 * Created on November 4, 2024, 12:11 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Cards.h"
#include "Deck.h"
#include <vector>

using namespace std;

class Player{
    private:
        float cash, bet;
        int handSize = 2;
        int handValue;
        bool hasAce;
        string name;
        vector<Cards> hand;
        int setHandValue();
    public:
        Player();
        Player(string);
        ~Player();
        void initializeHand();
        void drawCard(Deck *);
        void displayHand(bool);
        void setBet(float);
        void doubleBet();
        void winBet(bool);
        void loseBet();
        void pushBet();
        string getSuit(int);
        void setCash(int c){cash = c;}
        float getCash(){return cash;}
        float getBet(){return bet;}
        int getHandValue(){return handValue;}
        int getHandSize(){return handSize;}
        bool checkBust();
};

#endif /* PLAYER_H */

