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
	_model->cleanUp();
	char playerTypes[4];

	char playerType;
	for (int i = 0; i < 4; i++){

		playerType = (_view->getPlayerType(i)) ? 'h' : 'c';

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



