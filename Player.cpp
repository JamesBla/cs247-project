#include "Player.h"
#include "Card.h"

using namespace std;

Player::Player(View* view){
	_view = view;
}

int Player::getScore(){
	return _score;
}

int Player::getHandSize(){
	return _hand.size();
}

void Player::addCard(Card* card){
	_hand.push_back(card);
}