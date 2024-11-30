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