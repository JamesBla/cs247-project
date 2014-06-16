#include "ComputerPlayer.h"

typedef std::set<Card*, bool(*)(const Card*& lhs, const Card*& rhs)> CardSet;

ComputerPlayer::ComputerPlayer(CardSet *cs) : Player(cs){}

void ComputerPlayer::playTurn(){
	
}