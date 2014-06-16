#include "Player.h"
#include "Card.h"

Player::Player(CardSet* cs){
	_playedCards = cs;
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