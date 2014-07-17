#include "Subject.h"
#include "Observer.h"

void Subject::subscribe(Observer* o){
	_observers.insert(o);
}

void Subject::unsubscribe(Observer* o){
	_observers.erase(o);
}

void Subject::notify(){
	std::set<Observer*>::iterator i;

	for (i = _observers.begin(); i != _observers.end(); i++){
		(*i)->update();
	}
}
