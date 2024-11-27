/* 
 * File:   Player.h
 * Author: Adam Zavala
 * Purpose: Structure to hold player and dealer information
 * Created on November 4, 2024, 12:11 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Cards.h"

struct Player{
    float cash;
    int handSize = 2;
    int handValue;
    bool hasAce;
    vector<Cards> hand;
};

#endif /* PLAYER_H */

