#include "Model.h"
#include "View.h"
#include "Controller.h"

Controller::Controller(Model* model){
	this->_model = model;
}

void Controller::setView(View* view){
	this->_view = view;
}

void Controller::initiateModel(){
	char playerTypes[Model::getPlayerCount()];

	char playerType;
	for (int i = 0; i < Model::getPlayerCount(); i++){
		_view->requestPlayerType(i+1);
		cin >> playerType;
		playerTypes[i] = playerType;
	}

	_model->setPlayers(playerTypes);
}