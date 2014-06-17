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

vector<Card*> Player::getHand() const{
	return _hand;
}

bool Player::playable(Card* card, bool (&cardMap)[4][13]) const{
	int rank = card->getRank();
	int suit = card->getSuit();
	if (rank == SEVEN) {
		return true;
	} else if ((rank > 0 && cardMap[suit][rank-1]) || (rank < 12 && cardMap[suit][rank+1])) {
		return true;
	}
	return false;
}