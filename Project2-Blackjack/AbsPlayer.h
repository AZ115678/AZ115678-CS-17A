/* 
 * File:   AbsPlayer.h
 * Author: Adam Zavala
 *
 * Created on November 29, 2024, 3:46 PM
 */

#ifndef ABSPLAYER_H
#define ABSPLAYER_H

#include "Deck.h"
using namespace std;
class AbsPlayer{
    public:
        virtual void initializeHand() = 0;
        virtual void drawCard(Deck *) = 0;
        virtual void displayHand(bool) = 0;
        virtual string getSuit(int) = 0;
        virtual int getHandValue() = 0;
        virtual int getHandSize() = 0;
        
};

#endif /* ABSPLAYER_H */

