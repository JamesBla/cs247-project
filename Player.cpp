#include "Card.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

using namespace std;

Player::Player(Model* model, View* view, Controller* controller, int number){
	_view = view;
	_playerNumber = number;
	_model = model;
	_controller = controller;
	_score = 0;
	_roundScore = 0;
}

Player::Player(const Player& player){
	_hand = player._hand;
	_discards = player._discards;
	_score = player._score;
	_roundScore = player._roundScore;
	_view = player._view;
	_playerNumber = player._playerNumber;
	_model = player._model;
	_controller = player._controller;
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
			
			_discards.push_back(card);
			break;
		}
	}
}

void Player::updateScore(){
	for (int i = 0; i < _discards.size(); i++){
		_roundScore += (_discards[i]->getRank() + 1);
	}

	int newScore = _score + _roundScore;

	_view->printNewScore(_discards, _score, _roundScore, newScore, _playerNumber);
	_score = newScore;
}

void Player::prepForNewRound(){
	_discards.clear();
	_roundScore = 0;

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
	for (int i = 0; i < _hand.size(); i++){
		if (playable(_hand[i], cardMap)){
			legalCards.push_back(_hand[i]);
		}
		if (*(_hand[i]) == *(_model->sevenOfSpades())){
			legalCards.clear();
			legalCards.push_back(_hand[i]);
			return legalCards;
		}
	}
	return legalCards;
}

Controller* Player::getController() const{
	return _controller;
}
