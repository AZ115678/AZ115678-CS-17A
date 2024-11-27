/* 
 * File:   Cards.h
 * Author: Adam Zavala
 * Purpose: Structure that holds card information
 * Created on November 4, 2024, 12:08 PM
 */

#ifndef CARDS_H
#define CARDS_H
#include <string>
using namespace std;

enum Suit {SPADES, DIAMONDS, CLUBS, HEARTS};
const int SIZE = 80;
struct Cards {
    string name = "";
    Suit suit;
    int value;
};

#endif /* CARDS_H */

