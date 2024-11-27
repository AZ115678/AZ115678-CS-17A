/* 
 * File:   main.cpp
 * Author: Adam Zavala
 * Purpose: Project 2 - Simple Blackjack that displays concepts learned from chapters 9-12
 * Created on October 17, 2024, 12:13 PM
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

#include "Player.h"
#include "Deck.h"

void initializeHand(Player *, Player *, Deck *);
void playGame(Deck *, int);
void playHand(Deck *, Player *, Player *);
void saveFile(fstream &, Player *);
void readFile(fstream &, Player *);

int main(int argc, char** argv) {
    const int SIZE = 52;
    //creates array for Cards structure which will hold card information in deck like Queen of Hearts, etc
    //new deck object
    Deck *deck = new Deck;
    //create 52 card deck
    //deck = initializeDeck(SIZE);
    
    cout << "Welcome to the Blackjack table! \n" << endl;

    //shuffle deck
    //shuffleDeck(deck, SIZE);
    //gameplay loop
    playGame(deck, SIZE);
    //deck.shuffleDeck();
    delete deck;        
    return 0;
}

void initializeHand(Player *player, Player *dealer, Deck *deck){
    //clears and resets hands for both the player and dealer
    //player->hand.clear();
    //dealer->hand.clear();
    //player->handSize = 0;
    //dealer->handSize = 0;
    player->initializeHand();
    dealer->initializeHand();
    
    int draw = deck->getNumDraws() + 4;
    //for loop based on cardsDrawn integer which keeps track drawn cards so that each draw will simulate the next card that is coming up
    //ex: first card drawn is deck[0] and cardsDrawn is now 1. So next drawn card is deck[cardsDrawn] which is deck[1]
    for(int i=0;i<4;i++){
        switch(i%2){
            case 0:
                player->drawCard(deck);
                //player->hand.push_back(deck[cardsDrawn]);
                break;
            case 1:
                dealer->drawCard(deck);
                //dealer->hand.push_back(deck[cardsDrawn]);
                break;
        }
    }
}

void playGame(Deck *deck, int size){
    //creates player and dealer based on Player structure which holds information on cash available, and cards in hand
    Player *player = new Player;
    Player *dealer = new Player("Dealer");
    float bet;
    int cardsDrawn, shuffleMark;
    int *sPtr = nullptr;
    fstream dataFile;
    cardsDrawn = 0;
    shuffleMark = 36;
    sPtr = &shuffleMark;
    //checks for previous cash amount for returning player
    readFile(dataFile, player);
    //game loop that keeps going until player either quits or loses all their money
    while(player->getCash() > 0){
        //checks if the deck is in need of a reshuffling
        deck->checkShuffle();
        //player enters bet to get started
        cout << "Please enter bet (Cash: $" << player->getCash() << ")\n(Enter 0 to exit) : " << endl;
        cin >> bet;
        if(bet == 0){
            saveFile(dataFile, player);
            cout << "Thanks for playing!" << endl;
            return;
        }
        //input validation for player bet amount
        while(bet>player->getCash() || bet < 0){
            if(bet > player->getCash()){
                cout << "Enter bet that you can afford!" << endl;
            }
            else {
                cout << "Enter amount bigger than 0!" << endl;
            }

            cin >> bet;
        }
        player->setBet(bet);
        //once bet is placed, the player and dealer draws two
        initializeHand(player, dealer, deck);
        //playHand function is called to now start a game with our hand!
        playHand(deck, player, dealer);
        
    }
    cout << "You got kicked out the table for going broke...\n" << "Game Over" << endl;
    saveFile(dataFile, player);
    delete player;
    delete dealer;
}

void playHand(Deck *deck, Player *player, Player *dealer){
    const int SIZE = 80;
    bool stand, bust, blackjack;
    stand = false;
    bust = false;
    blackjack = false;
    char input[SIZE];
    //loops through until player either chooses to stand or busts
    cin.ignore();
    while(stand == false && bust == false){
        player->displayHand(stand);
        dealer->displayHand(stand);
        //checks if player has a blackjack from initial hand
        if(player->getHandValue() == 21 && player->getHandSize() == 2){
            cout << "BlackJack!" << endl;
            blackjack = true;
            stand = true;
        }
        else{
            //checks if player has already hit on current hand, if not they have the option to double bet
            if(player->getHandSize() == 2 && (player->getBet() <= player->getCash())){
                cout << "Hit, Stand, or Double?" << endl;
            }
            else{
                cout << "Hit or Stand?" << endl;
            }
            
            cin.getline(input, SIZE);
            
            if(strcmp(input, "stand") == 0 || strcmp(input, "Stand") == 0 || strcmp(input, "s") == 0){
                stand = true;
                cout << "Player stands at " << player->getHandValue() << "\n" << endl;
            }
            else if(strcmp(input, "hit") == 0 || strcmp(input, "Hit") == 0 || strcmp(input, "h") == 0){
                cout << "Player hits at " << player->getHandValue() << "\n" << endl;
                player->drawCard(deck);
            }
            else if(player->getHandSize() == 2 && (strcmp(input, "double") == 0 || strcmp(input, "Double") == 0 || strcmp(input, "d") == 0) && (player->getBet() <= player->getCash())){
                //player->cash = player->cash - bet;
                cout << "Player doubles bet of " << player->getBet() << endl;
                player->doubleBet();
                player->drawCard(deck);
                stand = true;
            }
        }
        bust = player->checkBust();
    }
    if(bust == true){
        stand = true;
        player->displayHand(stand);
        dealer->displayHand(stand);
        cout << "You lost..." << endl;
    }
    //after player action is done, check for any blackjack actions
    else if(blackjack == true){
        player->displayHand(stand);
        dealer->displayHand(stand);
        //checks if player and dealer both got blackjack from initial hand
        if(dealer->getHandValue() == 21){
            cout << "Dealer reveals a blackjack...\n"<<endl;
            player->pushBet();
        }
        //player gets a bigger payout for getting blackjack
        else{
            player->winBet(blackjack);
        }
    }
    //dealer's actions start if player action is done and no blackjack was drawn
    else{
        player->displayHand(stand);
        dealer->displayHand(stand);
        //dealer must hit on hand value 16 and below
        while(dealer->getHandValue() < 17){
            dealer->drawCard(deck);
            player->displayHand(stand);
            dealer->displayHand(stand);
        }
        //if statement that checks if player or dealer wins bet by comparing hands
        if(dealer->getHandValue() > 21){
            cout << "Dealer busts...\n"<< endl;
            player->winBet(blackjack);
        }
        else if(dealer->getHandValue() == 21 && dealer->getHandSize() == 2){
            cout << "Dealer reveals a blackjack...\n"<< endl;
            player->loseBet();
        }
        else if(player->getHandValue() > dealer->getHandValue()){
            player->winBet(blackjack);
        }
        else if(player->getHandValue() == dealer->getHandValue()){
            player->pushBet();
        }
        else{
            cout << "Dealer wins..." << endl;
            player->loseBet();
        }
    }
}
void readFile(fstream &data, Player *player){
    float cash;
    data.open("save.txt", ios::in | ios::binary);
    //creates new save file if none is found
    if(data.fail()){
        //cout << "Save file not found, creating new save file." << endl;
        data.open("save.txt", ios::out | ios::binary);
    }
    //loads previous cash amount. If 0 then resets to 200.
    else{
        //cout << "Save file loaded!" << endl;
        data.read(reinterpret_cast<char*>(&cash), sizeof(cash));
        player->setCash(cash);
        cout << "Welcome back!\n";
        if(player->getCash() <= 0){
            cout << "After losing all your money last time, you managed to acquire $200" << endl;
            player->setCash(200);
        }
    }
    data.close();
}

void saveFile(fstream &data, Player *player){
    //saves player cash for next time program is loaded
    float cash = player->getCash();
    data.open("save.txt", ios::out | ios::binary);
    data.write(reinterpret_cast<char*>(&cash), sizeof(cash));
    //cout << "File saved!" << endl;
    data.close();
}