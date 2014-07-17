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
	
	char playerTypes[4];

	char playerType;
	for (int i = 0; i < 4; i++){

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

Model* Controller::getModel(){
	return _model;
}

void Controller::requestCommand(HumanPlayer* player, vector<Card*>& legalPlays, vector<Card*>& hand){

}



