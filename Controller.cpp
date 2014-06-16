#include <iostream>

#include "Model.h"
#include "View.h"
#include "Controller.h"

using namespace std;

Controller::Controller(Model* model){
	this->_model = model;
}

void Controller::setView(View* view){
	this->_view = view;
}

void Controller::initializeModel(){
	char playerTypes[Model::getPlayerCount()];

	char playerType;
	for (int i = 0; i < Model::getPlayerCount(); i++){
		_view->requestPlayerType(i+1);
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

