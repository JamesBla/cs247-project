#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Model.h"
#include "View.h"

#include "Card.h"

#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

Card initSevenOfSpades(){
	Card c(SPADE, SEVEN);
	return c;
}
const Card Model::SEVEN_OF_SPADES = initSevenOfSpades();

const Card* Model::sevenOfSpades(){
	return &SEVEN_OF_SPADES;
}

std::vector<Card*> Model::getDeck() const{
	return _deck;
}

void Model::initializeDeck(){
	for (int suit = 0; suit < SUIT_COUNT; suit++){
		for (int rank = 0; rank < RANK_COUNT; rank++){
			Card* newCard = new Card(static_cast<Suit>(suit), static_cast<Rank>(rank));
			_deck.push_back(newCard);
		}
	}
}

void Model::clearCardsOnTable(){
	for (int suit = 0; suit < SUIT_COUNT; suit++){
		for (int rank = 0; rank < RANK_COUNT; rank++){
			_playedCards[suit][rank] = false;
		}
	}
}

Model::~Model(){
	clear();
}

void Model::computerizePlayer(Player* player){
	int playerIndex = player->getNumber() - 1;
	ComputerPlayer* computerPlayer = new ComputerPlayer(*player);
	delete player;
	_players[playerIndex] = computerPlayer;
	
	playATurn(NULL);
}

void Model::initializePlayers(char playerTypes[]){
	for (int i = 0; i < 4; i++){		
		if (playerTypes[i] == 'h'){
			_players.push_back(new HumanPlayer(this, i+1));
		}
		else{
			_players.push_back(new ComputerPlayer(this, i+1));
		}
	}
}

void Model::shuffle(){
	int n = 52;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = _deck[n];
		_deck[n] = _deck[k];
		_deck[k] = c;
	}
}

void Model::deal(){
	for (int i = 0; i < 52; i++){
		_players[i/13]->addCard(_deck.at(i));
		if (*_deck[i] == SEVEN_OF_SPADES){
			_firstPlayer = i/13;
		}
	}
}

void Model::putCardOnTable(Card* card){
	_playedCards[card->getSuit()][card->getRank()] = true;
}

bool Model::doneGame() const{
	return _doneGame;
}

void Model::playGame(){
	_doneGame = false;
	_startOfNewRound = false;
	_roundEnded = false;
	_roundInProgress = false;
	_resetView = false;

	playRound();
}

bool Model::beenPlayed(int rank, int suit) const{
	return _playedCards[rank][suit];
}

void Model::playRound() {
	notify();

	clearCardsOnTable();
	shuffle();
	deal();

	for (int i = 0; i < 4; i++){
		_players[i]->prepForNewRound();
	}

	_curPlayer = _firstPlayer;

	_roundEnded = false;
	_startOfNewRound = true;
	_roundInProgress = true;

	notify();

	_startOfNewRound = false;
	
	if (!_players[_curPlayer]->isHuman()){
		playATurn(NULL);
	}
}

void Model::playATurn(Card* card){
	// not sure why we needed this before
	// if (_players.size() == 0) return;

	// current player has no more cards. round is done.
	if (_players.at(_curPlayer)->getHandSize() == 0) {

		_doneGame = false;
		
		for (int i = 0; i < 4; i++) {
			_players[i]->updateScore();
			if (_players[i]->getScore() >= 80){
				_doneGame = true;
			}
		}

		_roundEnded = true;
		_roundInProgress = false;

		notify();

		_roundEnded = false;

		if (!_doneGame) {
			playRound();
		}
		else {
			cleanUp();
		}

		return;
	}

	// if the play is good, go to next player
	if (_players[_curPlayer]->playTurn(card, _playedCards)){
		_curPlayer = (_curPlayer + 1) % 4;
	}

	notify();

	// if the next player is computer or hand is empty, invoke the play
	if (!_players[_curPlayer]->isHuman() || _players.at(_curPlayer)->getHandSize() == 0){
		playATurn(NULL);
	}
}

vector<Card*> Model::getLegalPlays(Player* player){
	return player->getLegalPlays(_playedCards);
}

vector<Player*> Model::getWinners() const{
	int minScore = 1337;
	vector<Player*> winners;
	for (unsigned int i = 0; i < _players.size(); i++){
		int curScore = _players[i]->getScore();

		if (curScore <= minScore){

			if (curScore < minScore){
				minScore = curScore;
				winners.clear();
			}

			winners.push_back(_players[i]);
		}
	}
	return winners;
}

void Model::clear() {
	for (vector<Card*>::iterator it = _deck.begin(); it != _deck.end(); it++){
		delete *it;
	}

	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++){
		delete *it;
	}
}

void Model::cleanUp(){
	_resetView = true;
	notify();
	_resetView = false;

	clearCardsOnTable();
	
	clear();

	_deck.clear();
	_players.clear();
	_doneGame = _startOfNewRound = _roundEnded = _roundInProgress = false;
}

bool Model::resetView() const{
	return _resetView;
}

Card* Model::findCard(Card* target) const {
	for (unsigned int i = 0; i < _deck.size(); i++) {
		if (*target == *(_deck[i])){
			return _deck[i];
		}
	}
	return NULL;
}

Player* Model::getPlayer(int index) const {
	return _players.at(index);
}

Player* Model::getFirstPlayer() const {
	return getPlayer(_firstPlayer);
}

bool Model::isStartOfNewRound() const {
	return _startOfNewRound;
}

bool Model::isRoundFinished() const {
	return _roundEnded;
}

bool Model::isRoundInProgress() const {
	return _roundInProgress;
}

Player* Model::getCurrentPlayer() const{
	return _players.at(_curPlayer);
}

int Model::getPlayerScore(int playerIndex) const{
	if (_players.empty()) return 0;
	return _players.at(playerIndex)->getScore();
}

int Model::getPlayerDiscardedCount(int playerIndex) const{
	if (_players.empty()) return 0;
	return _players.at(playerIndex)->getDiscardedCount();
}

vector<Card*> Model::getDiscardedCards(int playerIndex) const{
	return _players.at(playerIndex)->getDiscarded();
}
