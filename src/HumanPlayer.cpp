#include <vector>

#include "Player.h"
#include "HumanPlayer.h"
#include "Model.h"
#include "Card.h"

using namespace std;

HumanPlayer::HumanPlayer(Model* model, int score, int roundScore, int oldScore, int number, 
			std::vector<Card*> hand, std::vector<Card*> discards) :
		Player(model, score, roundScore, oldScore, number, hand, discards){}

HumanPlayer::HumanPlayer(Model* model, int number) : Player(model, number){}

// plays card if card is a legal play, discards card selected if there are no legal plays
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
