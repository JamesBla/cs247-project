#include "ComputerPlayer.h"
#include <map>

#include <iostream>

using namespace std;

ComputerPlayer::ComputerPlayer(Model* model, View* view, Controller* controller, int number) : Player(model, view, controller, number){}

ComputerPlayer::ComputerPlayer(const HumanPlayer& humanPlayer): Player(humanPlayer) {}

void ComputerPlayer::playTurn(bool (&cardMap)[4][13]){
	vector<Card*> legalCards = getLegalPlays(cardMap);
	if (legalCards.size() > 0){
		playCard(legalCards.at(0));
	}
	else{
		discard(getHand().at(0));
	}
}