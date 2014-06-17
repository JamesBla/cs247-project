#include "HumanPlayer.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer(View* view) : Player(view){}

void HumanPlayer::playTurn(bool (&cardMap)[4][13]){
	vector<Card*> hand = getHand();

	getView()->printCardsOnTable(cardMap);
	getView()->printCardsInHand(hand);

	// populate legal plays
	vector<Card*> legalCards;
	for (vector<Card*>::iterator it = hand.begin(); it != hand.end(); it++){
		if (playable(*it, cardMap)){
			legalCards.push_back(*it);
		}
	}
	getView()->printLegalPlays(legalCards);
	getView()->printPrompt();

	string command;
	cin >> command;

}