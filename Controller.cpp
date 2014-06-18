#include <iostream>

#include "Model.h"
#include "View.h"
#include "Controller.h"
#include "Command.h"

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
		_view->requestPlayerType(i);
		cin >> playerType;
		playerTypes[i] = playerType;
	}

	_model->setPlayers(playerTypes);
	_model->initializeDeck();
}

void Controller::run(){
	initializeModel();
	_model->playGame();
}

void Controller::requestCommand(Player* player, vector<Card*>& legalPlays, vector<Card*>& hand){
	Command command;
	bool cardPlayLegal = false;
	while (!cin.eof()) {
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
			} else {
				_view->printIllegalPlay();
			}
		} else if (command.type == DISCARD) {
			if (legalPlays.size() != 0) {
				
				player->discard(c);
			}
			else{
				_view->printMayNotDiscard();
			}
			
		}
	}
}

