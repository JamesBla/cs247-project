#include <iostream>

#include "Model.h"
#include "View.h"
#include "Controller.h"

using namespace std;

View::View(Controller* controller, Model* model){
	controller->setView(this);
	model->setView(this);
}

void View::requestPlayerType(int playerNumber) const{
	cout << "Is player " << playerNumber << " a human(h) or a computer(c)?" << endl;
}

void View::announceNewRound(int firstPlayer) const{
	cout << "A new round begins. It’s player " << firstPlayer << "’s turn to play." << endl;
}