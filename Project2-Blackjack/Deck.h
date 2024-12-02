/* 
 * File:   Deck.h
 * Author: Adam Zavala
 *
 * Created on November 26, 2024, 6:26 PM
 */

#ifndef DECK_H
#define DECK_H
#include "Cards.h"
#include <string>

class Deck{
    private:
        static int cardsDrawn;
        int size, shuffleMarker;
        Cards *cards;
        Cards *initializeDeck(int);
        void shuffleDeck();
    public:
        Deck();
        ~Deck();
        void checkShuffle();
        void prntDeck();
        const int getNumDraws() const{return cardsDrawn;}
        Cards drawCard();
        const string getName(int) const;
        const string getSuit(int) const;
        
};

#endif /* DECK_H */

