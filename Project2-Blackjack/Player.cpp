/* 
 * File:   Player.h
 * Author: Adam Zavala
 * Purpose: 
 * Created on November 4, 2024, 12:11 PM
 */

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
Player::Player(string n, float c){
    cash = c;
    handSize = 0;
    name = n;
}
Player::Player(const Player&obj){
    name = obj.name;
    hand = obj.hand;
    handSize = obj.handSize;
    cash = obj.cash;
    bet = obj.bet;
    handValue = obj.handValue;
//    delete obj;
}
Player::~Player(){
    
}
void Player::displayHand(){
    cout << "\n\n\n" << name << "'s Hand: " << endl;
    for(int i=0;i<handSize;i++){
        cout << getCard(i) << endl;
    }
    handValue = setHandValue();
    cout << name <<" at " << handValue << ": \n" << endl;
}
void Player::setBet(float b){
    bet = b;
    cash -= b;
}
void Player::setInsurance(float ins){
    insurance = ins;
    cash -= ins;
}
void Player::doubleBet(){
    cash -= bet;
    bet = bet * 2;
}
void Player::winIns(bool ins){
    if(ins == true){
        cash += insurance * 2;
        cout << name << " wins insurance payout of $" << insurance * 2 << endl;
    }
}
void Player::winBet(bool blackjack){
    if(blackjack == true){
        cash += bet * 2.5;
        cout << name <<" wins $" << bet*2.5 << "!" << endl;
    }
    else{
        cash += bet * 2;
        cout << name << " wins $" << bet*2 << "!" << endl;
    }
}
void Player::pushBet(){
    cash += bet;
    cout << "Push! $" << bet << " returned." << endl;
}
void Player::loseBet(){
    cout << name << " lost bet of $" << bet << "..." << endl;
}
//overloaded ++ prefix operator
Player& Player::operator++(){
    cash += bet *2;
    cout << name <<" wins $" << bet*2 << "!" << endl;
    return *this;
}