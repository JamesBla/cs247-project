#include "HumanPlayer.h"

typedef std::set<Card*, bool(*)(const Card*& lhs, const Card*& rhs)> CardSet;

HumanPlayer::HumanPlayer(CardSet *cs) : Player(cs){}

void HumanPlayer::playTurn(){
	
}