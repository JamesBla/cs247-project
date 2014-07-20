#ifndef _CONTROLLER_
#define _CONTROLLER_

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
private:
	Model* _model;
};

#endif