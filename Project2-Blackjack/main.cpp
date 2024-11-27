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
void displayHand(Player *, Player *, bool);
void playGame(Deck *, int);
void playHand(Deck *, Player *, Player *, float);
string displaySuit(Suit);
int evaluateHand(Player *);
void drawCard(Deck *, Player *);
bool checkBust(Player *);
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
    player->hand.clear();
    dealer->hand.clear();
    player->handSize = 0;
    dealer->handSize = 0;
    int draw = deck->getNumDraws() + 4;
    //for loop based on cardsDrawn integer which keeps track drawn cards so that each draw will simulate the next card that is coming up
    //ex: first card drawn is deck[0] and cardsDrawn is now 1. So next drawn card is deck[cardsDrawn] which is deck[1]
    for(int i=0;i<4;i++){
        switch(i%2){
            case 0:
                drawCard(deck, player);
                //player->hand.push_back(deck[cardsDrawn]);
                break;
            case 1:
                drawCard(deck, dealer);
                //dealer->hand.push_back(deck[cardsDrawn]);
                break;
        }
    }
}

void playGame(Deck *deck, int size){
    //creates player and dealer based on Player structure which holds information on cash available, and cards in hand
    Player *player = new Player;
    Player *dealer = new Player;
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
    while(player->cash > 0){
        //checks if the deck is in need of a reshuffling
        deck->checkShuffle();
        //player enters bet to get started
        cout << "Please enter bet (Cash: $" << player->cash << ")\n(Enter 0 to exit) : " << endl;
        cin >> bet;
        if(bet == 0){
            saveFile(dataFile, player);
            cout << "Thanks for playing!" << endl;
            return;
        }
        //input validation for player bet amount
        while(bet>player->cash || bet < 0){
            if(bet > player->cash){
                cout << "Enter bet that you can afford!" << endl;
            }
            else {
                cout << "Enter amount bigger than 0!" << endl;
            }

            cin >> bet;
        }
        player->cash = player->cash - bet;
        //once bet is placed, the player and dealer draws two
        initializeHand(player, dealer, deck);
        //playHand function is called to now start a game with our hand!
        playHand(deck, player, dealer, bet);
        
    }
    cout << "You got kicked out the table for going broke...\n" << "Game Over" << endl;
    saveFile(dataFile, player);
    delete player;
    delete dealer;
}

void playHand(Deck *deck, Player *player, Player *dealer, float bet){
    const int SIZE = 80;
    bool stand, bust, blackjack;
    stand = false;
    bust = false;
    char input[SIZE];
    //loops through until player either chooses to stand or busts
    cin.ignore();
    while(stand == false && bust == false){
        displayHand(player, dealer, stand);
        //checks if player has a blackjack from initial hand
        if(player->handValue == 21 && player->handSize ==2){
            cout << "BlackJack!" << endl;
            blackjack = true;
            stand = true;
        }
        else{
            //checks if player has already hit on current hand, if not they have the option to double bet
            if(player->handSize == 2 && (bet <= player->cash)){
                cout << "Hit, Stand, or Double?" << endl;
            }
            else{
                cout << "Hit or Stand?" << endl;
            }
            
            cin.getline(input, SIZE);
            
            if(strcmp(input, "stand") == 0 || strcmp(input, "Stand") == 0 || strcmp(input, "s") == 0){
                stand = true;
                cout << "Player stands at " << player->handValue << "\n" << endl;
            }
            else if(strcmp(input, "hit") == 0 || strcmp(input, "Hit") == 0 || strcmp(input, "h") == 0){
                cout << "Player hits at " << player->handValue << "\n" << endl;
                drawCard(deck, player);
            }
            else if(player->handSize == 2 && (strcmp(input, "double") == 0 || strcmp(input, "Double") == 0 || strcmp(input, "d") == 0) && (bet <= player->cash)){
                player->cash = player->cash - bet;
                cout << "Player doubles bet of " << bet << endl;
                bet = bet * 2;
                drawCard(deck, player);
                stand = true;
            }
        }
        bust = checkBust(player);
    }
    if(bust == true){
        stand = true;
        displayHand(player, dealer, stand);
        cout << "You lost..." << endl;
    }
    //after player action is done, check for any blackjack actions
    else if(blackjack == true){
        displayHand(player, dealer, stand);
        //checks if player and dealer both got blackjack from initial hand
        if(dealer->handValue == 21){
            cout << "Dealer reveals a blackjack...\nPush! $" << bet << " returned." << endl;
            player->cash += bet;
        }
        //player gets a bigger payout for getting blackjack
        else{
            cout << "Player wins $" << (bet*2.5) << "!" << endl;
            player->cash += bet * 2.5;
        }
    }
    //dealer's actions start if player action is done and no blackjack was drawn
    else{
        displayHand(player, dealer, stand);
        //dealer must hit on hand value 16 and below
        while(dealer->handValue < 17){
            drawCard(deck, dealer);
            displayHand(player, dealer, stand);
        }
        //if statement that checks if player or dealer wins bet by comparing hands
        if(dealer->handValue > 21){
            cout << "Dealer busts...\nPlayer wins $" << (bet*2) << "!" << endl;
            player->cash += bet * 2;
        }
        else if(player->handValue > dealer->handValue){
            cout << "Player wins $" << (bet*2) << "!" << endl;
            player->cash += bet * 2;
        }
        else if(player->handValue == dealer->handValue){
            cout << "Push! $" << bet << " returned." << endl;
            player->cash += bet;
        }
        else{
            cout << "Dealer wins..." << endl;
        }
    }
}
//simulate drawing card by adding push back on vector based on cardsDrawn int
void drawCard(Deck *deck, Player *drawer){
    drawer->handSize ++;
    //cout << deck->getName(deck->getNumDraws()) << " of " << deck->getSuit(deck->getNumDraws()) << " revealed!\n" << endl;
    drawer->hand.push_back(deck->drawCard());
    
}

void displayHand(Player *player, Player *dealer, bool stand){ 
    cout << "\nPlayer Hand: " << endl;
    for(int i=0;i<player->handSize;i++){
        cout << player->hand[i].name << " of " << displaySuit(player->hand[i].suit) << endl;
    }
    //evaluate hand
    
    player->handValue = evaluateHand(player);
    //if hand includes ace then it displays both hand values if true
    if(player->hasAce == true && player->handValue <= 21){
        cout << "Player at " << (player->handValue-10) << "/" << player->handValue <<": \n" << endl;
    }
    else{
        cout << "Player at " << player->handValue << ": \n" << endl;
    }
    
    cout << "Dealer Hand:" << endl;
    //does not reveal dealer's hand until player ends all actions
    if(stand == false){
        cout << dealer->hand[0].name << " of " << displaySuit(dealer->hand[0].suit) << endl;
        cout << "Dealer's second card is currently face down.\n" << endl;
    }
    else{
        for(int i=0;i<dealer->handSize;i++){
            cout << dealer->hand[i].name << " of " << displaySuit(dealer->hand[i].suit) << endl;
        }
        dealer->handValue = evaluateHand(dealer);
        cout << "Dealer is at " << dealer->handValue << "\n" << endl;
    }
    
}

void readFile(fstream &data, Player *player){
    data.open("save.txt", ios::in | ios::binary);
    //creates new save file if none is found
    if(data.fail()){
        //cout << "Save file not found, creating new save file." << endl;
        data.open("save.txt", ios::out | ios::binary);
        player->cash = 500;
    }
    //loads previous cash amount. If 0 then resets to 200.
    else{
        //cout << "Save file loaded!" << endl;
        data.read(reinterpret_cast<char*>(&player->cash), sizeof(player->cash));
        cout << "Welcome back!\n";
        if(player->cash <= 0){
            cout << "After losing all your money last time, you managed to acquire $200" << endl;
            player->cash = 200;
        }
    }
    data.close();
}

void saveFile(fstream &data, Player *player){
    //saves player cash for next time program is loaded
    data.open("save.txt", ios::out | ios::binary);
    data.write(reinterpret_cast<char*>(&player->cash), sizeof(player->cash));
    //cout << "File saved!" << endl;
    data.close();
}

string displaySuit(Suit s){
    string suit;
    
    switch(s){
        case(SPADES): suit = "Spades"; break;
        case(DIAMONDS): suit = "Diamonds"; break;
        case(CLUBS): suit = "Clubs"; break;
        case(HEARTS): suit = "Hearts"; break;
    }
    
    return suit;
}

int evaluateHand(Player *player){
    player->handValue = 0;
    player->hasAce = false;
    int size = player->handSize;
    int handValue = 0;
    //loop that counts total hand value and checks if ace is part of hand
    for(int i=0;i<size;i++){
        if(player->hand[i].name == "Ace"){
            player->hasAce = true;
        }
        handValue += player->hand[i].value;
    }
    //if player has an ace card they have two potential hand values
    if(player->hasAce == true && handValue <= 11){
        handValue += 10;
    }
    return handValue;
}
//function that checks for a bust event
bool checkBust(Player *player){
    bool bust;
    player->handValue = evaluateHand(player);
    if(player->handValue > 21){
        bust = true;
        cout << "Bust!" << endl;
    }
    else{
        bust = false;
    }
    return bust;
}