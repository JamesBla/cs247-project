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
	cout << "Is player " << playerNumber + 1 << " a human(h) or a computer(c)?\n";
	printPrompt();
}

void View::announceNewRound(int firstPlayer) const{
	cout << "A new round begins. It’s player " << firstPlayer + 1 << "’s turn to play." << endl;
}

void View::printCardsOnTable(string suits[4]) const{
	cout << "Cards on the table:\n";
	cout << "Clubs: " << suits[0] << endl;
	cout << "Diamonds: " << suits[1] << endl;
	cout << "Hearts: " << suits[2] << endl;
	cout << "Spades: " << suits[3] << endl;
}

void View::printCardsInHand(string hand) const{
	cout << "Your hand: " << hand << endl;
}

void View::printLegalPlays(string plays) const{
	cout << "Legal plays: " << plays << endl;
}

void View::printPrompt() const{
	cout << ">";
}
