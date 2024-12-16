/* 
 * File:   Player.h
 * Author: Adam Zavala
 * Purpose: 
 * Created on November 4, 2024, 12:11 PM
 */

#include "Deck.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cstring>
#include <string.h>

using namespace std;

int Deck::cardsDrawn = 0;
//deck constructor
Deck::Deck(){
    size = 52;
    shuffleMarker = 36;
    cards = initializeDeck(size);
    shuffleDeck();
    
    //prntDeck();
}
//deletes Cards array
Deck::~Deck(){
    delete []cards;
}
//sets up new Cards array with respective values
Cards *Deck::initializeDeck(int size){
    //for loop to fill new Cards array with information like suit, name, and values based on order
    //will be shuffled in a separate function
    Cards *deck;
    deck = new Cards[size];
    for(int i=0;i<size;i++){
        if(i >= 0 && i < 13){
            deck[i].suit = SPADES;
        }
        else if(i >= 13 && i < 26){
            deck[i].suit = DIAMONDS;
        }
        else if(i >= 26 && i < 39){
            deck[i].suit = CLUBS;
        }
        else{
            deck[i].suit = HEARTS;
        }
        switch(i%13){
            case 0:
                deck[i].name = "Ace";
                deck[i].value = 1;
                break;
            case 1:
                deck[i].name = "Two";
                deck[i].value = 2;
                break;
            case 2:
                deck[i].name = "Three";
                deck[i].value = 3;
                break;
            case 3:
                deck[i].name = "Four";
                deck[i].value = 4;
                break;
            case 4:
                deck[i].name = "Five";
                deck[i].value = 5;
                break;
            case 5:
                deck[i].name = "Six";
                deck[i].value = 6;
                break;
            case 6:
                deck[i].name = "Seven";
                deck[i].value = 7;
                break;
            case 7:
                deck[i].name = "Eight";
                deck[i].value = 8;
                break;
            case 8:
                deck[i].name = "Nine";
                deck[i].value = 9;
                break;
            case 9:
                deck[i].name = "Ten";
                deck[i].value = 10;
                break;
            case 10:
                deck[i].name = "Jack";
                deck[i].value = 10;
                break;
            case 11:
                deck[i].name = "Queen";
                deck[i].value = 10;
                break;
            case 12:
                deck[i].name = "King";
                deck[i].value = 10;
                break;
        }
    }
    return deck;
}
//Shuffles deck
void Deck::shuffleDeck(){
    int x = time(0);
    srand(x);
    Cards tempCard;
    //nested for loop that generates number between 0-51 to swap card order in.
    //loops 9 times for better randomization
    for(int j=0;j<9;j++){
        for(int i=0;i<size;i++){
            int randNum = rand() % 52;
            tempCard = cards[randNum];
            cards[randNum] = cards[i];
            cards[i] = tempCard;
        }
    }
    cardsDrawn = 0;
    //cout that was used to make sure this function was called
    cout << "Deck Shuffled!\n" << endl;
}
//Function that checks if the deck is ready to be shuffled again
void Deck::checkShuffle(){
    if(cardsDrawn >= shuffleMarker){
        shuffleDeck();
    }
}
void Deck::prntDeck(){
    for(int i=0;i<size;i++){
        cout << getName(i) << " of " << getSuit(i) << endl;
    }
}
//Function to draw next card
Cards Deck::drawCard(){
    Cards c;
    c = cards[cardsDrawn];
    cardsDrawn ++;
    return c;
}
//Function that returns a specific card's name
const string Deck::getName(int index) const{
    string n;
    n = cards[index].name;
    return n;
}
//Function that returns a specific card's suit
const string Deck::getSuit(int index) const{
    string n;
    switch(cards[index].suit){
        case(SPADES): n = "Spades"; break;
        case(DIAMONDS): n = "Diamonds"; break;
        case(CLUBS): n = "Clubs"; break;
        case(HEARTS): n = "Hearts"; break;
    }
    return n;
}