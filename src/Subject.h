#ifndef _SUBJECT_
#define _SUBJECT_

#include <set>

class Observer;

class Subject{
public:
	void subscribe(Observer*);			// subscribes an observer
	void unsubscribe(Observer*);		// unsubscribes an observer

protected:
	void notify();						// notify observers that model changed

private:
	std::set<Observer*> _observers;
};

#endif