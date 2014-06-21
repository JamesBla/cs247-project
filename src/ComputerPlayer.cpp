#include <vector>

#include "Player.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"

using namespace std;

class Model;
class View;
class Controller;

class Card;

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