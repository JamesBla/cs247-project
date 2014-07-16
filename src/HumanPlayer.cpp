#include <vector>

#include "Player.h"
#include "HumanPlayer.h"
#include "Controller.h"
#include "View.h"


using namespace std;

HumanPlayer::HumanPlayer(Model* model, View* view, Controller* controller, int number) : Player(model, view, controller, number){}

void HumanPlayer::playTurn(bool (&cardMap)[4][13]){
	vector<Card*> hand = getHand();

	// getView()->printCardsOnTable(cardMap);

	// need to update table after each playTurn();

	getView()->notify();

	// populate legal plays
	vector<Card*> legalCards = getLegalPlays(cardMap);
	getView()->printLegalPlays(legalCards);
	getController()->requestCommand(this, legalCards, hand);
	
}

bool HumanPlayer::isHuman() const{
	return true;
}