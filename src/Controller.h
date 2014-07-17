#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <vector>

class Model;
class View;

class HumanPlayer;
class Card;

class Controller{
public:
	Controller(Model* model);
	void run();
	void initializeModel();
	void setView(View* view);
	void requestCommand(HumanPlayer*, std::vector<Card*>&, std::vector<Card*>&);
	Model* getModel();
private:
	Model* _model;
	View* _view;
};

#endif