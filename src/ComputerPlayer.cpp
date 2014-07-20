#include <vector>

#include "Player.h"
#include "ComputerPlayer.h"

using namespace std;

class Model;
class Card;

ComputerPlayer::ComputerPlayer(Model* model, int score, int roundScore, int oldScore, int number, 
		std::vector<Card*> hand, std::vector<Card*> discards) :
	Player(model, score, roundScore, oldScore, number, hand, discards){}

ComputerPlayer::ComputerPlayer(Model* model, int number) : Player(model, number){}

ComputerPlayer::ComputerPlayer(const Player& player): Player(player) {}

// plays or discards first valid card
bool ComputerPlayer::playTurn(Card* card, bool (&cardMap)[4][13]){
	vector<Card*> legalCards = getLegalPlays(cardMap);
	if (legalCards.size() > 0){
		playCard(legalCards.at(0));
	}
	else{
		discard(getHand().at(0));
	}
	return true;
}

bool ComputerPlayer::isHuman() const{
	return false;
}