#ifndef _VIEW_
#define _VIEW_

#include "Model.h"
#include "Controller.h"
class Model;
class Controller;
class View{
public:
	View(Controller*, Model*);
	void requestPlayerType(int) const;
};

#endif