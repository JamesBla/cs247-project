#include <vector>

#include "Player.h"
#include "HumanPlayer.h"
#include "Controller.h"
#include "View.h"
#include "Model.h"
#include "Card.h"

#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer(Model* model, View* view, Controller* controller, int number) : Player(model, view, controller, number){}

bool HumanPlayer::playTurn(Card* card, bool (&cardMap)[4][13]){
	vector<Card*> hand = getHand();

	// getView()->printCardsOnTable(cardMap);

	// need to update table after each playTurn();

	// populate legal plays
	
	vector<Card*> legalPlays = getLegalPlays(cardMap);

	bool cardPlayLegal = false;

	for (vector<Card*>::iterator it = legalPlays.begin(); it != legalPlays.end(); it++){
		// cout << card << endl;
		if (*(*it) == *card){
			
			cardPlayLegal = true;
			break;
		}
	}

	// cout << "bye" << endl;

	if (cardPlayLegal){
		playCard(card);
	} else if (legalPlays.empty()){
		discard(card);
	} else{
		return false;
	}
	return true;

	// getView()->printLegalPlays(legalCards);
	// getController()->requestCommand(this, legalCards, hand); 
	
}

bool HumanPlayer::isHuman() const{
	return true;
}