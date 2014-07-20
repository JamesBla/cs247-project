#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <string>

class Model;
class Card;

class Controller{
public:
	Controller(Model* model);
	void run();							// runs the game
	void endGame();						// ends the game
	void initializeModel();				// initializes data in model
	void setSeed(int);					// sets seed
	void playRound();					// plays a round
	void playATurn(Card* card);			// plays a turn for a player
	void computerizePlayer(int);		// computerizes specified player (ragequit)
	void togglePlayer(int);				// toggles between computer and human player types
	void saveGame(std::string);			// exports game to a gamesave file
	void loadSavedFile(std::string);	// imports game from gamesave file
private:
	Model* _model;
};

#endif