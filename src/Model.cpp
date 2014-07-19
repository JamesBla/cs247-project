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

bool Model::beenPlayed(int rank, int suit) const{
	return _playedCards[rank][suit];
}

void Model::updateScoreAndEndGame() {
	for (int i = 0; i < 4; i++) {
		_players[i]->updateScore();
		if (_players[i]->getScore() >= 80){
			_doneGame = true;
		}
	}
	notify();
	_state = ROUND_ENDED;
	notify();
	if (_doneGame) {
		_state = GAME_ENDED;
		notify();
	}
}

bool Model::playTurn(Card *card) {
	return _players[_curPlayer]->playTurn(card, _playedCards);
}

void Model::advanceCurrentPlayer() {
	_curPlayer = (_curPlayer + 1) % 4;
	notify();
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
	_state = RESET_VIEW;
	notify();
	_state = NONE;

	clearCardsOnTable();
	
	clear();

	_deck.clear();
	_players.clear();
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

Model::State Model::getState() const {
	return _state;
}

void Model::setState(State state) {
	_state = state;
	notify();
}

void Model::setCurrentPlayer(int playerIndex) {
	_curPlayer = playerIndex;
}

Player* Model::getCurrentPlayer() const{
	return _players.at(_curPlayer);
}

int Model::getPlayerScore(int playerIndex) const{
	if (_players.empty()) return 0;
	return _players.at(playerIndex)->getScore();
}

int Model::getPlayerCurrentRoundScore(int playerIndex) const{
	if (_players.empty()) return 0;
	return _players.at(playerIndex)->getRoundScore();
}

int Model::getPlayerDiscardedCount(int playerIndex) const{
	if (_players.empty()) return 0;
	return _players.at(playerIndex)->getDiscardedCount();
}

vector<Card*> Model::getDiscardedCards(int playerIndex) const{
	return _players.at(playerIndex)->getDiscarded();
}
