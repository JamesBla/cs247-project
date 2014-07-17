#ifndef _SUBJECT_
#define _SUBJECT_

#include <set>

class Observer;

class Subject{
public:
	void subscribe(Observer*);
	void unsubscribe(Observer*);

protected:
	void notify();

private:
	std::set<Observer*> _observers;
};

#endif