#include "Player.h"
#include "Card.h"

using namespace std;

Player::Player(map<Card*, bool>* cardMap){
	_playedCards = cardMap;
}

int Player::getScore(){
	return _score;
}

int Player::getHandSize(){
	return _hand.size();
}

void Player::addCard(Card* card){
	_hand.insert(card);
}