#include "Dealer.h"

Dealer::Dealer(){
    name = "Dealer";
}
Dealer::~Dealer(){
    
}
void Dealer::initializeHand(){
    hand.clear();
    handSize = 0;
}
void Dealer::drawCard(Deck *deck){
    handSize ++;
    hand.push_back(deck->drawCard());
    handValue = setHandValue();
}
void Dealer::displayHand(bool stand){
    cout << "\n" << name << "'s Hand: " << endl;
    if(stand == false){
        cout << getCard(0) << endl;
        cout << "Dealer's second card is currently face down.\n" << endl;
    }
    else{
        for(int i=0;i<handSize;i++){
            cout << getCard(i) << endl;
        }
        //handValue = setHandValue();
        cout << name << " is at " << handValue << "\n" << endl;
    }
}
string Dealer::getCard(int index){
    string cardInfo = "";
    string suit;
    
    cardInfo += hand[index].name;
    switch(hand[index].suit){
        case(SPADES): suit = "Spades"; break;
        case(DIAMONDS): suit = "Diamonds"; break;
        case(CLUBS): suit = "Clubs"; break;
        case(HEARTS): suit = "Hearts"; break;
    }
    cardInfo += " of " + suit;
    return cardInfo;
}
int Dealer::setHandValue(){
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
bool Dealer::checkBust(){
    bool bust;
    handValue = setHandValue();
    if(handValue > 21){
        bust = true;
        cout << name <<" busts..." << endl;
    }
    else{
        bust = false;
    }
    return bust;
}

bool Dealer::operator > (Dealer *right){
    bool status;
    if(handValue > right->getHandValue()){
        status = true;
    }
    else{
        status = false;
    }
    return status;
}
bool Dealer::operator == (Dealer *right){
    bool status;
    if(handValue == right->getHandValue()){
        status = true;
    }
    else{
        status = false;
    }
    return status;
}