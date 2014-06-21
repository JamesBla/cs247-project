#include <iostream>
#include <string>

#include "Model.h"
#include "View.h"
#include "Controller.h"

#include "Player.h"
#include "Card.h"


using namespace std;

View::View(Controller* controller, Model* model){
	controller->setView(this);
	model->setView(this);
}

void View::printNewScore(std::vector<Card*>& discards, int oldScore, int gainedScore, int newScore, int playerNumber) const{
	cout << "Player " << playerNumber << "'s discards: ";
	for (unsigned int i = 0; i < discards.size(); i++){
		cout << *(discards[i]);
		if (i != discards.size() - 1){
			cout << " ";
		}
	}
	cout << endl;
	cout << "Player " << playerNumber << "'s score: " << oldScore << " + " << gainedScore << " = " << newScore << endl;
}

void View::requestPlayerType(int playerNumber) const{
	cout << "Is player " << playerNumber + 1 << " a human(h) or a computer(c)?\n";
}

void View::announceNewRound(int firstPlayer) const{
	cout << "A new round begins. It's player " << firstPlayer + 1 << "'s turn to play." << endl;
}

void View::printCardsOnTable(const bool (&cardMap)[4][13]) const{
	string onTable[4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			if (cardMap[i][j]) {
				string rankPrintForm;
				switch(j) {
					case 0:
						rankPrintForm = "A";
						break;
					case 9:
						rankPrintForm = "10";
						break;
					case 10:
						rankPrintForm = 'J';
						break;
					case 11:
						rankPrintForm = 'Q';
						break;
					case 12:
						rankPrintForm = 'K';
						break;
					default:
						rankPrintForm = static_cast<char>(j+49);
				}
				onTable[i] = onTable[i] + rankPrintForm + " ";
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

void View::printLegalPlay(Player*& player, Card*& card) const{
	cout << "Player " << player->getNumber() << " plays " << *card << "." << endl;
};

void View::printIllegalPlay() const{
	cout << "This is not a legal play.\n";
}

void View::printDiscard(Player*& player, Card*& card) const{
	cout << "Player " << player->getNumber() << " discards " << *card << "." << endl;
}

void View::printMayNotDiscard() const{
	cout << "You have a legal play. You may not discard." << endl;
}

void View::announceWinner(int playerNumber) const{
	cout << "Player " << playerNumber << " wins!" << endl;
}

void View::printDeck(vector<Card*> & deck) const{
	for (unsigned int i = 0; i < deck.size(); i++){
		cout << *deck[i];
		if ((i + 1) % 13 == 0){
			cout << endl;
		}
		else{
			cout << " ";
		}
	}
}