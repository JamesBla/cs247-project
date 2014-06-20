#include "HumanPlayer.h"
#include "Controller.h"

#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

HumanPlayer::HumanPlayer(Model* model, View* view, Controller* controller, int number) : Player(model, view, controller, number){}

void HumanPlayer::playTurn(bool (&cardMap)[4][13]){
	vector<Card*> hand = getHand();

	getView()->printCardsOnTable(cardMap);
	getView()->printCardsInHand(hand);

	// populate legal plays
	vector<Card*> legalCards = getLegalPlays(cardMap);
	
	getView()->printLegalPlays(legalCards);
	
	getController()->requestCommand(this, legalCards, hand);
	
}