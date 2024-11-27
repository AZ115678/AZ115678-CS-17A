#include "Player.h"
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;
Player::Player(){
    cash = 500;
    handSize = 0;
    name = "Player";
}
Player::Player(string n){
    cash = 500;
    handSize = 0;
    name = n;
}
Player::~Player(){
    
}
void Player::initializeHand(){
    hand.clear();
    handSize = 0;
}
void Player::drawCard(Deck *deck){
    handSize ++;
    hand.push_back(deck->drawCard());
}
void Player::displayHand(bool stand){
    cout << "\n" << name << " Hand: " << endl;
    if(name == "Player"){
        for(int i=0;i<handSize;i++){
            cout << hand[i].name << " of " << getSuit(i) << endl;
        }
        handValue = setHandValue();
        cout << "Player at " << handValue << ": \n" << endl;
    }
    else{
        if(stand == false){
            cout << hand[0].name << " of " << getSuit(0) << endl;
            cout << "Dealer's second card is currently face down.\n" << endl;
        }
        else{
            for(int i=0;i<handSize;i++){
                cout << hand[i].name << " of " << getSuit(i) << endl;
            }
            handValue = setHandValue();
            cout << "Dealer is at " << handValue << "\n" << endl;
        }
    }
    
}
void Player::setBet(float b){
    bet = b;
    cash -= b;
}
void Player::doubleBet(){
    cash -= bet;
    bet = bet * 2;
}
void Player::winBet(bool blackjack){
    if(blackjack == true){
        cash += bet * 2.5;
        cout << "Player wins $" << bet*2.5 << "!" << endl;
    }
    else{
        cash += bet * 2;
        cout << "Player wins $" << bet*2 << "!" << endl;
    }
}
void Player::pushBet(){
    cash += bet;
    cout << "Push! $" << bet << " returned." << endl;
}
void Player::loseBet(){
    cout << "You lost your bet of $" << bet << "..." << endl;
}
string Player::getSuit(int index){
    string suit;
    
    switch(hand[index].suit){
        case(SPADES): suit = "Spades"; break;
        case(DIAMONDS): suit = "Diamonds"; break;
        case(CLUBS): suit = "Clubs"; break;
        case(HEARTS): suit = "Hearts"; break;
    }
    
    return suit;
}
int Player::setHandValue(){
    handValue = 0;
    hasAce = false;
    for(int i=0;i<handSize;i++){
        if(hand[i].name == "Ace"){
            hasAce = true;
        }
        handValue += hand[i].value;
    }
    if(hasAce == true && handValue <= 11){
        handValue += 10;
    }
    return handValue;
}
bool Player::checkBust(){
    bool bust;
    handValue = setHandValue();
    if(handValue > 21){
        bust = true;
        cout << "Bust!" << endl;
    }
    else{
        bust = false;
    }
    return bust;
}