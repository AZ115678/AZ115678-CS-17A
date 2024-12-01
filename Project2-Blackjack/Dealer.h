/* 
 * File:   Dealer.h
 * Author: Adam Zavala
 *
 * Created on November 29, 2024, 4:47 PM
 */

#ifndef DEALER_H
#define DEALER_H

#include "AbsPlayer.h"
#include <vector>
#include <iostream>
class Dealer : public AbsPlayer{
    protected:
        int handSize, handValue;
        bool hasAce;
        string name;
        vector<Cards> hand;
        int setHandValue();
    public:
        Dealer();
        ~Dealer();
        virtual void initializeHand();
        virtual void drawCard(Deck *);
        virtual void displayHand(bool);
        virtual string getSuit(int);
        virtual int getHandValue(){return handValue;}
        virtual int getHandSize(){return handSize;}
        bool checkBust();
        bool operator > (Dealer *);
        bool operator == (Dealer *);
};


#endif /* DEALER_H */

