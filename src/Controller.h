#ifndef _CONTROLLER_
#define _CONTROLLER_

class Model;

class Controller{
public:
	Controller(Model* model);
	void run(int, char[4]);
	void endGame();
	void initializeModel(char[4]);
private:
	Model* _model;
};

#endif