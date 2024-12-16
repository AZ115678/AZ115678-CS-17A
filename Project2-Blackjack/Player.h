/* 
 * File:   Player.h
 * Author: Adam Zavala
 * Purpose: 
 * Created on November 4, 2024, 12:11 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Dealer.h"
#include "Cards.h"
#include <vector>

using namespace std;

class Player : public Dealer{
    private:
        float cash, bet, insurance;
        
    public:
        Player();
        Player(string);
        Player(string, float);
        //copy constructor
        Player(const Player &);
        ~Player();
        void displayHand();     //Polymorphic from dealer class
        void setBet(float);
        void setInsurance(float);
        void doubleBet();
        void winIns(bool);
        void winBet(bool);
        void loseBet();
        void pushBet();
        void setCash(int c){cash = c;}
        float getCash(){return cash;}
        float getBet(){return bet;}
        float getInsurance(){return insurance;}
        string getName(){return name;}
        Player& operator++();
};

#endif /* PLAYER_H */