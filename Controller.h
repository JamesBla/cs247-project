#ifndef _CONTROLLER_
#define _CONTROLLER_

#include "Model.h"
#include "View.h"

class Controller{
	
public:
	Controller(Model*);
	void initiateModel();
	void setView(View*);
private:
	Model* _model;
	View* _view;
};

#endif