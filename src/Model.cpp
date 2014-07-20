#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
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

Model::Model() : _seed(0) {
	for (int i = 0; i < 4; i++) {
		_playerTypes[i] = 'h';
	}
}

void Model::initializePlayers() {
	for (int i = 0; i < 4; i++){
		if (_playerTypes[i] == 'h'){
			_players.push_back(new HumanPlayer(this, i+1));
		}
		else{
			_players.push_back(new ComputerPlayer(this, i+1));
		}
	}
}

void Model::initializeDeck(){
	for (int suit = 0; suit < SUIT_COUNT; suit++){
		for (int rank = 0; rank < RANK_COUNT; rank++){
			Card* newCard = new Card(static_cast<Suit>(suit), static_cast<Rank>(rank));
			_deck.push_back(newCard);
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

void Model::computerizePlayer(int playerIndex){
	Player* player = _players.at(playerIndex);
	ComputerPlayer* computerPlayer = new ComputerPlayer(*player);
	delete player;
	_players[playerIndex] = computerPlayer;
}

void Model::updateScoreAndEndGame() {
	int doneGame = false;
	for (int i = 0; i < 4; i++) {
		_players[i]->updateScore();
		if (_players[i]->getScore() >= 80){
			doneGame = true;
		}
	}
	notify();
	_state = ROUND_ENDED;
	notify();
	if (doneGame) {
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

void Model::setState(State state) {
	_state = state;
	notify();
}

void Model::setCurrentPlayer(int playerIndex) {
	_curPlayer = playerIndex;
}

void Model::setSeed(int seed) {
	_seed = seed;
}

void Model::setPlayerType(int playerIndex, char type) {
	_playerTypes[playerIndex] = type;
}

void Model::cleanUp(){
	_state = RESET_VIEW;
	notify();
	_state = NONE;

	clearCardsOnTable();

	deleteCardsAndPlayers();

	_deck.clear();
	_players.clear();
}

void Model::clearCardsOnTable(){
	for (int suit = 0; suit < SUIT_COUNT; suit++){
		for (int rank = 0; rank < RANK_COUNT; rank++){
			_playedCards[suit][rank] = false;
		}
	}
}

void Model::deleteCardsAndPlayers() {
	for (vector<Card*>::iterator it = _deck.begin(); it != _deck.end(); it++){
		delete *it;
	}

	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++){
		delete *it;
	}
}

Model::~Model(){
	deleteCardsAndPlayers();
}

Card* Model::findCard(Card* target) const {
	for (unsigned int i = 0; i < _deck.size(); i++) {
		if (*target == *(_deck[i])){
			return _deck[i];
		}
	}
	return NULL;
}

bool Model::beenPlayed(int rank, int suit) const{
	return _playedCards[rank][suit];
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

vector<Card*> Model::getLegalPlays(Player* player){
	return player->getLegalPlays(_playedCards);
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

vector<Card*> Model::getDeck() const{
	return _deck;
}

int Model::getSeed() const{
	return _seed;
}

char Model::getPlayerType(int playerIndex) const{
	return _playerTypes[playerIndex];
}

void Model::exportModel(ofstream& file) {
	file << _seed << endl;
	file << _state << endl;
	file << _firstPlayer << endl;
	file << _curPlayer << endl;
	for (int i = 0; i < 4; i++) {
		file << _playerTypes[i] << endl;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			file << _playedCards[i][j] << endl;
		}
	}
	for (unsigned int i = 0; i < _deck.size(); i++) {
		file << *(_deck[i]) << endl;
	}
	for (int i = 0; i < 4; i++) {
		file << "player\n";
		file << *(_players[i]);
	}
}

void Model::reconstructModel(ifstream& file) {
	file >> _seed;
	int state;
	file >> state;
	_state = static_cast<State>(state);
	file >> _firstPlayer >> _curPlayer;
	for (int i = 0; i < 4; i++) {
		file >> _playerTypes[i];
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			file >> _playedCards[i][j];
		}
	}
	for (int i = 0; i < 52; i++) {
		Card* newCard = new Card(static_cast<Suit>(0), static_cast<Rank>(0));
		file >> *newCard;
		_deck.push_back(newCard);
	}
	// TODO read players from text file, recreate them
	notify();
}
