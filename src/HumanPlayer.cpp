#include <vector>

#include "Player.h"
#include "HumanPlayer.h"
#include "Model.h"
#include "Card.h"

using namespace std;

HumanPlayer::HumanPlayer(Model* model, int number) : Player(model, number){}

bool HumanPlayer::playTurn(Card* card, bool (&cardMap)[4][13]){
	vector<Card*> hand = getHand();
	
	vector<Card*> legalPlays = getLegalPlays(cardMap);

	bool cardPlayLegal = false;

	for (vector<Card*>::iterator it = legalPlays.begin(); it != legalPlays.end(); it++){
		if (*(*it) == *card){
			
			cardPlayLegal = true;
			break;
		}
	}

	if (cardPlayLegal){
		playCard(card);
	} else if (legalPlays.empty()){
		discard(card);
	} else{
		return false;
	}
	return true;
}

bool HumanPlayer::isHuman() const{
	return true;
}