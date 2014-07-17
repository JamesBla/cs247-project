#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Model.h"
#include "View.h"
#include "Controller.h"

#include "Card.h"

#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

const int Model::PLAYER_COUNT = 4;
const int Model::CARD_COUNT = 52;

Card initSevenOfSpades(){
	Card c(SPADE, SEVEN);
	return c;
}
const Card Model::SEVEN_OF_SPADES = initSevenOfSpades();

const Card* Model::sevenOfSpades(){
	return &SEVEN_OF_SPADES;
}

void Model::setView(View* view){
	this->_view = view;
}

std::vector<Card*> Model::getDeck() const{
	return _deck;
}

void Model::setController(Controller* controller){
	_controller = controller;
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
	cleanUp();
}

int Model::getPlayerCount(){
	return Model::PLAYER_COUNT;
}

void Model::computerizePlayer(HumanPlayer* humanPlayer){
	int playerIndex = humanPlayer->getNumber() - 1;
	ComputerPlayer* computerPlayer = new ComputerPlayer(*humanPlayer);
	delete humanPlayer;
	_players[playerIndex] = computerPlayer;
	_curPlayer = (_curPlayer - 1) % 4;
}

void Model::initializePlayers(char playerTypes[]){
	for (int i = 0; i < PLAYER_COUNT; i++){
		assert(playerTypes[i] == 'h' || playerTypes[i] == 'c' || playerTypes[i] == 'H' || playerTypes[i] == 'C');
		
		if ((playerTypes[i] == 'h' || playerTypes[i] == 'H') ){
			_players.push_back(new HumanPlayer(this, _view, _controller, i+1));
		}
		else{
			_players.push_back(new ComputerPlayer(this, _view, _controller, i+1));
		}
	}
}

void Model::shuffle(){
	int n = CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		Card *c = _deck[n];
		_deck[n] = _deck[k];
		_deck[k] = c;
	}
}

void Model::deal(){
	for (int i = 0; i < CARD_COUNT; i++){
		_players[i/(CARD_COUNT/PLAYER_COUNT)]->addCard(_deck.at(i));
		if (*_deck[i] == SEVEN_OF_SPADES){
			_firstPlayer = i/(CARD_COUNT/PLAYER_COUNT);
		}
	}
}

void Model::putCardOnTable(Card* card){
	_playedCards[card->getSuit()][card->getRank()] = true;
}

void Model::playGame(){
	startOfNewRound = false;
	roundEnded = false;
	roundInProgress = false;
	// each loop iteration is a round
	// bool doneGame = 0;
	
	// // this loop is the whole game
	// do{
		
		playRound();
		// this loop is a round
		// do {
		// 	_players[_curPlayer]->playTurn(_playedCards);
		// 	_curPlayer = (_curPlayer + 1) % 4;
		// }
		// while(_players[_curPlayer]->getHandSize() > 0);

		// // round is over. now we update scores
		// for (int i = 0; i < PLAYER_COUNT; i++){
		// 	_players[i]->updateScore();
		// 	if (_players[i]->getScore() >= 80){
		// 		doneGame = true;
		// 	}
		// }

	// } while(!doneGame);

	// _view->announceWinners(getWinners());
}

bool Model::beenPlayed(int rank, int suit) const{
	return _playedCards[rank][suit];
}

void Model::playRound() {
	for (int i = 0; i < 4; i++) {
		_players[i]->updateScore();
		if (_players[i]->getScore() >= 80){
			cout << "Score exceeded 80\n";
			return;
		}
	}
	_view->notify();
	cout << "about to clear shuffle deal\n";
	clearCardsOnTable();
	shuffle();
	deal();
	roundEnded = false;
	for (int i = 0; i < PLAYER_COUNT; i++){
		_players[i]->prepForNewRound();
	}

	//_view->announceNewRound(_players[_firstPlayer]);
	_curPlayer = _firstPlayer;

	startOfNewRound = true;
	roundInProgress = true;
	_view->notify();
	startOfNewRound = false;
	cout << "first playturn" << endl;

	if (!_players[_curPlayer]->isHuman()){
		playATurn(NULL);
	}

	playRound();
}

void Model::playATurn(Card* card){
	//need to check if hand is empty, then end round
	if (_players.at(_curPlayer)->getHandSize() == 0) {
		cout << "hand size is zero";
		roundEnded = true;
		roundInProgress = false;
		_view->notify();
		roundEnded = false;
		return;
	}

	cout << "hi" << endl;
	//increment player if good play
	if (_players[_curPlayer]->playTurn(card, _playedCards)){
		_curPlayer = (_curPlayer + 1) % 4;
	}
	cout << "bye" << endl;

	if (!_players[_curPlayer]->isHuman()){
		playATurn(NULL);
	}

	_view->notify();
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

void Model::cleanUp(){
	for (vector<Card*>::iterator it = _deck.begin(); it != _deck.end(); it++){
		delete *it;
	}

	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++){
		delete *it;
	}
}

Card* Model::findCard(Card* target) const {
	for (unsigned int i = 0; i < _deck.size(); i++) {
		if (*target == *(_deck[i])){
			return _deck[i];
		}
	}
	return NULL;
}

Player* Model::getFirstPlayer() const {
	return _players.at(_firstPlayer);
}

Player* Model::getPlayer(int index) const {
	return _players.at(index);
}

bool Model::isStartOfNewRound() const {
	return startOfNewRound;
}

bool Model::isRoundFinished() const {
	return roundEnded;
}

bool Model::isRoundInProgress() const {
	return roundInProgress;
}

Player* Model::getCurrentPlayer() const{
	return _players.at(_curPlayer);
}

int Model::getPlayerScore(int playerIndex) const{
	return _players.at(playerIndex)->getScore();
}

int Model::getPlayerDiscardedCount(int playerIndex) const{
	return _players.at(playerIndex)->getDiscardedCount();
}

vector<Card*> Model::getDiscardedCards(int playerIndex) const{
	return _players.at(playerIndex)->getDiscarded();
}