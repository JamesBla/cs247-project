#ifndef _CONTROLLER_
#define _CONTROLLER_

#include "Model.h"
#include "View.h"

class Model;
class View;
class Controller{
	
public:
	Controller(Model* model);
	void run();
	void initializeModel();
	void setView(View* view);
private:
	Model* _model;
	View* _view;
};

#endif