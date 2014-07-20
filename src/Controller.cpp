#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Model.h"
#include "Controller.h"
#include "Player.h"

class Card;

using namespace std;

Controller::Controller(Model* model) {
	this->_model = model;
}

// initializes state variable, players, deck
void Controller::initializeModel() {
	_model->cleanUp();
	_model->initializePlayers();
	_model->initializeDeck();

	_model->setState(Model::NONE);
}

// initialize RNG using seed and starts the game
void Controller::run() {
	srand48(_model->getSeed());
	initializeModel();
	playRound();
}

void Controller::playRound() {
	// clear table, shuffle, deal
	_model->clearCardsOnTable();
	_model->shuffle();
	_model->deal();

	// reset round scores
	for (int i = 0; i < 4; i++){
		_model->getPlayer(i)->prepForNewRound();
	}

	// determines first player, sets states (and notifies view)
	_model->setCurrentPlayer(_model->getFirstPlayer()->getNumber()-1);
	_model->setState(Model::ROUND_STARTED);
	_model->setState(Model::IN_PROGRESS);

	// manually invoke playATurn for computer players
	if (!_model->getCurrentPlayer()->isHuman()){
		playATurn(NULL);
	}
}

void Controller::playATurn(Card* card) {
	// if the current player's hand is empty, round is done
	if (_model->getCurrentPlayer()->getHandSize() == 0) {
		_model->updateScoreAndEndGame();

		if (_model->getState() == Model::GAME_ENDED) {
			// if score >= 80, game is done
			_model->cleanUp();
		} else {
			// otherwise, start a new round
			playRound();
		}

		return;
	}

	// if the selected card is valid, go to next player
	if (_model->playTurn(card)) {
		_model->advanceCurrentPlayer();
	}

	// recursively call this method if next player
	// is computer or next player has no cards (in which
	// case the round needs to end)
	if (!_model->getCurrentPlayer()->isHuman() || _model->getCurrentPlayer()->getHandSize() == 0) {
		playATurn(NULL);
	}
}

// converts humanPlayer to computerPlayer and
// invokes playTurn for the new computerPlayer
void Controller::computerizePlayer(int playerIndex) {
	_model->computerizePlayer(playerIndex);
	_model->setPlayerType(playerIndex, 'c');
	playATurn(NULL);
}

// toggles player type
void Controller::togglePlayer(int playerIndex) {
	(_model->getPlayerType(playerIndex) == 'h') ? _model->setPlayerType(playerIndex, 'c') : _model->setPlayerType(playerIndex, 'h');
}

void Controller::setSeed(int seed){
	_model->setSeed(seed);
}

void Controller::endGame() {
	_model->cleanUp();
}

// exports Model with specified filename
void Controller::saveGame(string filename) {
	ofstream file(filename.c_str());
	if (file.is_open()) {
		_model->exportModel(file);
		file.close();
	}
}

// imports Model from file called filename
void Controller::loadSavedFile(string filename) {
	_model->cleanUp();
	ifstream file(filename.c_str());
	if (file.is_open()) {
		_model->importModel(file);
		file.close();
	}
}
