#include "HumanPlayer.h"
#include <map>
#include <string>

using namespace std;

HumanPlayer::HumanPlayer(View* view) : Player(view){}

void HumanPlayer::playTurn(bool (&cardMap)[4][13]){
	string onTable[4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			if (cardMap[i][j]) {
				onTable[i] += j+1 + " ";
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		if (onTable[i] != "") {
			onTable[i] = obTable[i].substr(0, onTable[i].length()-1);
		}
	}
}