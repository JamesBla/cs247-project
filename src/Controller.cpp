#include <cstdlib>
#include <iostream>

#include "Model.h"
#include "View.h"
#include "Controller.h"

#include "Command.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "Card.h"

using namespace std;

Controller::Controller(Model* model){
	this->_model = model;
	model->setController(this);
}

void Controller::setView(View* view){
	this->_view = view;
}

void Controller::initializeModel(){
	char playerTypes[Model::getPlayerCount()];

	char playerType;
	for (int i = 0; i < Model::getPlayerCount(); i++){

		playerType = (_view->requestPlayerType(i))? 'h' : 'c';

		playerTypes[i] = playerType;
	}

	_model->initializePlayers(playerTypes);
	_model->initializeDeck();
}

void Controller::run(){
	initializeModel();
	_model->playGame();
}

void Controller::requestCommand(HumanPlayer* player, vector<Card*>& legalPlays, vector<Card*>& hand){
	
	Command command;
	bool cardPlayLegal = false;
	while(true) {
		_view->printPrompt();
		cin >> command;

		Card* c = &(command.card);
		if (command.type == PLAY) {

			for (vector<Card*>::iterator it = legalPlays.begin(); it != legalPlays.end(); it++){
				if (*(*it) == command.card){
					cardPlayLegal = true;
					break;
				}
			}

			if (cardPlayLegal){
				player->playCard(c);
				break;
			} else {
				_view->printIllegalPlay();
			}

		} else if (command.type == DISCARD) {
			if (legalPlays.size() == 0) {
				player->discard(_model->findCard(c));
				break;
			}
			else{
				_view->printMayNotDiscard();
			}	
		} else if (command.type == DECK) {
			std::vector<Card*> deck = this->_model->getDeck();
			_view->printDeck(deck);
		} else if (command.type == QUIT){
			_model->cleanUp();
			exit(0);
		} else if (command.type == RAGEQUIT){
			_view->printRagequit(player);
			_model->computerizePlayer(player);
			break;

		}
	}
}



