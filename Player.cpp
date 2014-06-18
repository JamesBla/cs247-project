#include "Player.h"
#include "Card.h"

using namespace std;

Player::Player(View* view, Model* model, int number){
	_view = view;
	_playerNumber = number;
	_model = model;
}

int Player::getScore() const{
	return _score;
}

int Player::getHandSize() const{
	return _hand.size();
}

int Player::getNumber() const{
	return _playerNumber;
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

void Player::playCard(Card*& card){
	for (vector<Card*>::iterator it = _hand.begin(); it != _hand.end(); it++){
		if (*(*it) == *(card)){
			_hand.erase(it);
			Player* p = this;
			_view->printLegalPlay(p, card);
			_model->putCardOnTable(card);
			break;
		}
	}
}

void Player::discard(Card*& card){
	for (vector<Card*>::iterator it = _hand.begin(); it != _hand.end(); it++){
		if (*(*it) == *(card)){
			_hand.erase(it);
			Player* p = this;
			_view->printDiscard(p, card);
			_score += (card->getRank() + 1);
			_discards.push_back(card);
			break;
		}
	}
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

vector<Card*> Player::getLegalPlays(bool (&cardMap)[4][13]) const{
	// populate legal plays
	vector<Card*> legalCards;
	for (vector<Card*>::const_iterator it = _hand.begin(); it != _hand.end(); it++){
		if (playable(*it, cardMap)){
			legalCards.push_back(*it);
		}
	}
	return legalCards;
}
