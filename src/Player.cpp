#include "Model.h"

#include "Player.h"
#include "Card.h"

using namespace std;

Player::Player(Model* model, int number){
	_playerNumber = number;
	_model = model;
	
	_score = 0;
	_roundScore = 0;
	_oldScore = 0;
}

Player::Player(const Player& player){
	_hand = player._hand;
	_discards = player._discards;
	_score = player._score;
	_roundScore = player._roundScore;
	_oldScore = player._oldScore;
	_playerNumber = player._playerNumber;
	_model = player._model;
}

Player::~Player() {};

int Player::getScore() const{
	return _score;
}

int Player::getRoundScore() const{
	return _roundScore;
}

int Player::getOldScore() const{
	return _oldScore;
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

vector<Card*> Player::getHand() const{
	return _hand;
}

void Player::playCard(Card* card){ //play card by value
	for (vector<Card*>::iterator it = _hand.begin(); it != _hand.end(); it++){
		if (*(*it) == *(card)){
			_hand.erase(it);
			_model->putCardOnTable(card);
			break;
		}
	}
}

void Player::discard(Card* card){
	for (vector<Card*>::iterator it = _hand.begin(); it != _hand.end(); it++){
		if (*(*it) == *(card)){
			_hand.erase(it);
			_discards.push_back(card);
			_roundScore += card->getRank() + 1;
			break;
		}
	}
}

void Player::updateScore(){
	_oldScore = _score;
	_score = _oldScore + _roundScore;
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
	for (unsigned int i = 0; i < _hand.size(); i++){
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

int Player::getDiscardedCount() const{
	return _discards.size();
}

vector<Card*> Player::getDiscarded() const{
	return _discards;
}
