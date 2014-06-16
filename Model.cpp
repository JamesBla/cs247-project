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
static Card SevenOfSpades = initSevenOfSpades();

void Model::setView(View* view){
	this->_view = view;
}

void Model::initializeDeck(){
	for (int suit = 0; suit < SUIT_COUNT; suit++){
		for (int rank = 0; rank < RANK_COUNT; rank++){
			_deck.push_back(new Card(static_cast<Suit>(suit), static_cast<Rank>(rank)));
		}
	}
}

Model::~Model(){
	for (vector<Card*>::iterator it = _deck.begin(); it != _deck.end(); it++){
		delete *it;
	}

	for (vector<Player*>::iterator it = _players.begin(); it != _players.end(); it++){
		delete *it;
	}
	
}

int Model::getPlayerCount(){
	return Model::PLAYER_COUNT;
}

void Model::setPlayers(char playerTypes[]){
	for (int i = 0; i < PLAYER_COUNT; i++){
		assert(playerTypes[i] == 'h' || playerTypes[i] == 'c' || playerTypes[i] == 'H' || playerTypes[i] == 'C');
		
		if ((playerTypes[i] == 'h' || playerTypes[i] == 'H') ){
			_players.push_back(new HumanPlayer());
		}
		else{
			_players.push_back(new ComputerPlayer());
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
		if (*_deck[i] == SevenOfSpades){
			_firstPlayer = i/13 + 1;
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

void Model::playGame(){
	// each loop iteration is a round
	while (getMaxScore() < 80){
		// shuffle
		shuffle();
		// deal
		deal();
		int minHandSize = 1000;

		_view->announceNewRound(_firstPlayer);
		int curPlayer = _firstPlayer;
		do {
			_players[curPlayer]->playTurn();

			// calculate min hand size
			for (int i = 0; i < PLAYER_COUNT; i++){
				if (_players[i]->getHandSize() < minHandSize){
					minHandSize = _players[i]->getHandSize();
				}
			}
			curPlayer++;
		}
		while(minHandSize > 0);
	}
}