#ifndef _CONTROLLER_
#define _CONTROLLER_

class Model;
class View;

class Controller{
public:
	Controller(Model* model);
	void run();
	void initializeModel();
	void setView(View* view);
	Model* getModel();
private:
	Model* _model;
	View* _view;
};

#endif