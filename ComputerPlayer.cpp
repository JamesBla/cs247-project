#include "ComputerPlayer.h"
#include <map>

using namespace std;

ComputerPlayer::ComputerPlayer(View* view, Model* model, int number): Player(view, model, number){}

void ComputerPlayer::playTurn(bool (&cardMap)[4][13]){
	vector<Card*> legalCards = getLegalPlays(cardMap);
	if (legalCards.size() > 0){
		playCard(legalCards.at(0));
	}
	else{
		discard(getHand().at(0));
	}
}