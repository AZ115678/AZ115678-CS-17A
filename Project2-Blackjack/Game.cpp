#include "Game.h"
#include <iostream>
#include <cstring>

using namespace std;

Game::Game(){
    deck = new Deck;
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
        //function that retrieves bet and validates input
        bet = validateBet<float>();
        //if input is 0, player quits game
        if(bet == 0){
            //saveFile(dataFile, player);
            cout << "Thanks for playing!" << endl;
            return;
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
        player->displayHand();
        dealer->displayHand(stand);
        cout << player->getName() <<" lost..." << endl;
        playerConfirmation();
    }
    //after player action is done, check for any blackjack actions
    else if(blackjack == true){
        player->displayHand();
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
        playerConfirmation();
    }
    //dealer's actions start if player action is done and no blackjack was drawn
    else{
        dealerActions();
        //checks if player wins after dealer actions are complete
        winConditions();
    }
}
template <typename T>
T Game::validateBet(){
    bool validated = false;
    int bet;
    //loop that iterates until user inputs a proper bet amount
    while(validated == false){
        cout << "Please enter bet (Cash: $" << player->getCash() << ")\n(Enter 0 to exit) : " << endl;
        try{
            //checks if input is a number, if not then it throws an error
            if(!(cin>>bet)){
                cin.clear();
                cin.ignore();
                string exceptionString = "Please enter a number!\n";
                throw exceptionString;
            }
            //checks if bet is within player's means
            if(bet>player->getCash() || bet < 0){
                if(bet > player->getCash()){
                    string exceptionString = "Enter bet that you can afford!\n";
                    throw exceptionString;
                }
                else{
                    string exceptionString = "Enter amount bigger than 0!\n";
                    throw exceptionString;
                }
            }
            //if the program reaches this point then input is valid
            validated = true;
        }
        catch(string exceptionString){
            cout << exceptionString;
        }
    }
    
    return bet;
    
}
void Game::playerActions(){
    const int SIZE = 80;
    char input[SIZE];
    //loops through until player either chooses to stand or busts
    cin.ignore();
    while(stand == false && bust == false){
        player->displayHand();
        dealer->displayHand(stand);
        //checks if player has a blackjack from initial hand
        if(player->getHandValue() == 21 && player->getHandSize() == 2){
            cout << "BlackJack!" << endl;
            blackjack = true;
            stand = true;
        }
        else if(player->getHandValue() == 21){
            cout << "Twenty One!" << endl;
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
                cout << "Player draws " << player->getCard(player->getHandSize()-1) << endl;
            }
            else if(player->getHandSize() == 2 && (strcmp(input, "double") == 0 || strcmp(input, "Double") == 0 || strcmp(input, "d") == 0) && (player->getBet() <= player->getCash())){
                //player->cash = player->cash - bet;
                cout << "Player doubles bet of " << player->getBet() << endl;
                player->doubleBet();
                player->drawCard(deck);
                cout << "Player draws " << player->getCard(player->getHandSize()-1) << endl;
                stand = true;
            }
        }
        
        playerConfirmation();
        bust = player->checkBust();
        if(bust == true){
            playerConfirmation();
        }
    }
}
void Game::playerConfirmation(){
    //used to help player keep track of what is going on
    string confirm;
    cout << "\n(Press enter to continue) " << endl;
    getline(cin, confirm);
}
void Game::dealerActions(){
    //player->displayHand();
    int draw = 0;
    cout << "\nDealer's Turn." << endl;
    playerConfirmation();
    dealer->displayHand(stand);
    if(dealer->getHandValue() < 17){
        //dealer must hit on hand value 16 and below
        while(dealer->getHandValue() < 17){
            dealer->drawCard(deck);
            cout << "Dealer draws " << dealer->getCard(dealer->getHandSize() - 1) << endl;
            cout << "Dealer is at " << dealer->getHandValue();
            playerConfirmation();
            draw ++;
        }
    }
    player->displayHand();
    dealer->displayHand(stand);
    
}
void Game::winConditions(){
    //if statement that checks if player or dealer wins bet by comparing hands
    //checks if dealer busts
    if(dealer->checkBust()){
        player->winBet(blackjack);
    }
    //checks for blackjack
    else if(dealer->getHandValue() == 21 && dealer->getHandSize() == 2){
        cout << "Dealer reveals a blackjack...\n"<< endl;
        player->loseBet();
    }
    //compares hand with overloaded > relational operator
    else if(player->operator >(dealer)){
        //
        Player temp(*player);
        *player = ++temp;
        player->winBet(blackjack);
    }
    //checks for push with overloaded == relational operator
    else if(player->operator ==(dealer)){
        player->pushBet();
    }
    else{
        cout << "Dealer wins..." << endl;
        player->loseBet();
    }
    playerConfirmation();
}
void Game::loadGame(){
    char input;
    input = validateInput();
    if(input == 'Y' || input == 'y'){
        loadProfile();
    }
    else{
        newProfile();
    }
}
char Game::validateInput(){
    char input;
    cout << "Would you like to start a new profile or load previous profile?"
            << "\n(Y = load profile / N = new profile): ";
    cin >> input;
    while((input != 'Y' && input != 'y') && (input != 'N' && input != 'n') ){
        cout << "Would you like to start a new profile or load previous profile?"
            << "\n(Y = load profile / N = new profile): ";
        cin.clear();
        cin >> input;
        cout << input;
    }
    return input;
}
void Game::loadProfile(){
    string name;
    float cash;
    data.open("save.txt", ios::in);
    //creates new save file if none is found
    if(data.fail()){
        cout << "Save file not found, creating new save file." << endl;
        data.open("save.txt", ios::out);
        player = new Player;
    }
    //loads previous cash amount. If 0 then resets to 200.
    else{
        //cout << "Save file loaded!" << endl;
        getline(data, name);
        data >> cash;
        player = new Player(name, cash);
        cout <<endl;
        cout << "Welcome back " << player->getName() << "!\n";
        //checks if player lost all money from last game and resets cash to 200 if true
        if(player->getCash() <= 0){
            cout << "After losing all your money last time, you managed to acquire $200\n" << endl;
            player->setCash(200);
        }
    }
    data.close();
}
void Game::newProfile(){
    //inputs user name to use in player constructor
    string input;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, input);
    player = new Player(input);
}
void Game::saveGame(){
    //saves player cash for next time program is loaded
    float cash = player->getCash();
    string name = player->getName();
    data.open("save.txt", ios::out);
    data << name << endl;
    data << cash;
    data.close();
}