/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Deck.h
 * Author: buddy
 *
 * Created on November 26, 2024, 6:26 PM
 */

#ifndef DECK_H
#define DECK_H
#include "Cards.h"
#include <string>

class Deck{
    private:
        int size, cardsDrawn, shuffleMarker;
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

