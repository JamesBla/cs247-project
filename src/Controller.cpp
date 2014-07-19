#include <cstdlib>

#include "Model.h"
#include "Controller.h"

using namespace std;

Controller::Controller(Model* model){
	this->_model = model;
}

void Controller::initializeModel(char playerTypes[4]){
	_model->cleanUp();
	_model->initializePlayers(playerTypes);
	_model->initializeDeck();
}

void Controller::run(int seed, char playerTypes[4]){
	srand48(seed);
	initializeModel(playerTypes);
	_model->playGame();
}

void Controller::endGame(){
	_model->cleanUp();
}
