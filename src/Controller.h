#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <string>

class Model;
class Card;

class Controller{
public:
	Controller(Model* model);
	void run();
	void endGame();
	void initializeModel();
	void setSeed(int);
	void playRound();
	void playATurn(Card* card);
	void computerizePlayer(int);
	void togglePlayer(int);
	void saveGame(std::string);
	void loadSavedFile(std::string);
private:
	Model* _model;
};

#endif