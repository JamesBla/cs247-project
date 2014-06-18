#include <iostream>
#include <string>

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

void View::printCardsOnTable(const bool (&cardMap)[4][13]) const{
	string onTable[4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			if (cardMap[i][j]) {
				onTable[i] = onTable[i] + static_cast<char>(j+1+48) + " ";
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		if (onTable[i] != "") {
			onTable[i] = onTable[i].substr(0, onTable[i].length()-1);
		}
	}

	cout << "Cards on the table:\n";
	cout << "Clubs: " << onTable[0] << endl;
	cout << "Diamonds: " << onTable[1] << endl;
	cout << "Hearts: " << onTable[2] << endl;
	cout << "Spades: " << onTable[3] << endl;
}

void View::printCardsInHand(const std::vector<Card*> &cards) const{
	cout << "Your hand:";
	for (vector<Card*>::const_iterator it = cards.begin(); it != cards.end(); it++) {
		cout << " " << **it;
	}
	cout << endl;
}

void View::printLegalPlays(const std::vector<Card*> &cards) const{
	cout << "Legal plays:";
	for (vector<Card*>::const_iterator it = cards.begin(); it != cards.end(); it++) {
		cout << " " << **it;
	}
	cout << endl;
}

void View::printPrompt() const{
	cout << ">";
}

void View::printLegalPlay(int player, Card*& card) const{
	cout << "Player " << player << " " << *card << endl;
};

void View::printIllegalPlay() const{
	cout << "This is not a legal play.\n";
	printPrompt();
}
