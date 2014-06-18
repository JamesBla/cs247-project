#include "HumanPlayer.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer(View* view, Model* model, int number) : Player(view, model, number){}

void HumanPlayer::playTurn(bool (&cardMap)[4][13]){
	vector<Card*> hand = getHand();

	getView()->printCardsOnTable(cardMap);
	getView()->printCardsInHand(hand);

	// populate legal plays
	vector<Card*> legalCards = getLegalPlays(cardMap);
	getView()->printLegalPlays(legalCards);
	getView()->printPrompt();

	string command;
	cin >> command;

}