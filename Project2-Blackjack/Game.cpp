#include "Game.h"
#include <iostream>
#include <cstring>

using namespace std;

Game::Game(){
    deck = new Deck;
    player = new Player;
    dealer = new Dealer;
}
Game::~Game(){
    delete player;
    delete dealer;
    delete deck;
}
void Game::initializeHand(){
    //clears and resets hands for both the player and dealer
    player->initializeHand();
    dealer->initializeHand();
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
void Game::playGame(){
    float bet;
    while(player->getCash() > 0){
        //checks if the deck is in need of a reshuffling
        deck->checkShuffle();
        //player enters bet to get started
        cout << "Please enter bet (Cash: $" << player->getCash() << ")\n(Enter 0 to exit) : " << endl;
        cin >> bet;
        if(bet == 0){
            //saveFile(dataFile, player);
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
        initializeHand();
        //playHand function is called to now start a game with our hand!
        playHand();
    }
    cout << "You got kicked out the table for going broke...\n" << "Game Over" << endl;
}
void Game::playHand(){
    
    stand = false;
    bust = false;
    blackjack = false;
    
    playerActions();
    
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
        dealerActions();
    }
}
void Game::playerActions(){
    const int SIZE = 80;
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
}
void Game::dealerActions(){
    player->displayHand(stand);
    dealer->displayHand(stand);
    //dealer must hit on hand value 16 and below
    while(dealer->getHandValue() < 17){
        dealer->drawCard(deck);
        player->displayHand(stand);
        dealer->displayHand(stand);
    }
    //if statement that checks if player or dealer wins bet by comparing hands
    //checks if dealer busts
    if(dealer->getHandValue() > 21){
        cout << "Dealer busts...\n"<< endl;
        player->winBet(blackjack);
    }
    //checks for blackjack
    else if(dealer->getHandValue() == 21 && dealer->getHandSize() == 2){
        cout << "Dealer reveals a blackjack...\n"<< endl;
        player->loseBet();
    }
    //compares hand
    else if(player->getHandValue() > dealer->getHandValue()){
        player->winBet(blackjack);
    }
    //checks for push
    else if(player->getHandValue() == dealer->getHandValue()){
        player->pushBet();
    }
    else{
        cout << "Dealer wins..." << endl;
        player->loseBet();
    }
}
void Game::loadGame(){
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
void Game::saveGame(){
    //saves player cash for next time program is loaded
    float cash = player->getCash();
    data.open("save.txt", ios::out | ios::binary);
    data.write(reinterpret_cast<char*>(&cash), sizeof(cash));
    //cout << "File saved!" << endl;
    data.close();
}