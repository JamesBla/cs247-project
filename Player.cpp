#include "Player.h"
#include "Card.h"

using namespace std;

Player::Player(View* view){
	_view = view;
}

int Player::getScore() const{
	return _score;
}

int Player::getHandSize() const{
	return _hand.size();
}

void Player::addCard(Card* card){
	_hand.push_back(card);
}

View* Player::getView() const{
	return _view;
}