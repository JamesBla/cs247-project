#include <cassert>
#include <cstdlib>

#include "Card.h"
#include "Model.h"
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
static const Card SEVEN_OF_SPADES = initSevenOfSpades();

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

void Model::setPlayers(char playerTypes[]){
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

int Model::getMaxScore() const{
	int maxScore = 0;
	for (int i = 0; i < PLAYER_COUNT; i++){
		if (_players[i]->getScore() > maxScore){
			maxScore = _players[i]->getScore();
		}
	}
	return maxScore;
}

void Model::putCardOnTable(Card* &card){
	_playedCards[card->getSuit()][card->getRank()] = true;
}

void Model::playGame(){
	// each loop iteration is a round
	while (getMaxScore() < 80){
		// shuffle
		shuffle();
		// deal
		deal();
		int minHandSize = 1000;

		_view->announceNewRound(_firstPlayer);
		_curPlayer = _firstPlayer;
		do {

			_players[_curPlayer]->playTurn(_playedCards);

			_curPlayer = (_curPlayer + 1) % 4;
			
			// calculate min hand size
			for (int i = 0; i < PLAYER_COUNT; i++){
				if (_players[i]->getHandSize() < minHandSize){
					minHandSize = _players[i]->getHandSize();
				}
			}
			
		}
		while(minHandSize > 0);
	}
}

void Model::cleanUp(){
	for (vector<Card*>::iterator it = _deck.begin(); it != _deck.end(); it++){
		delete *it;
	}

	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++){
		delete *it;
	}
}