#ifndef _CONTROLLER_
#define _CONTROLLER_

class Model;
class Card;

class Controller{
public:
	Controller(Model* model);
	void run(int, char[4]);
	void endGame();
	void initializeModel(char[4]);
	void playRound();
	void playATurn(Card* card);
	void computerizePlayer();
private:
	Model* _model;
};

#endif