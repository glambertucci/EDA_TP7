#include <allegro5\allegro.h>
#include <vector>
#include "Timer.h"
#include "Stage.h"
#include "allegro_ctrl.h"
#include "Ev_t.h"
using namespace std;

/*
// Tenes que mover la funcion getEvent, setEvent

class EventHandler {
public:
	EventHandler();
	bool getEvent(ALLEGRO_EVENT_QUEUE *  eq);		// Gets the event from the event queue and/or other mediums not yet implemented
	bool isThereEvent();							// Checks if there is an active event
	void handleEventDispatcher(Stage& stage);		// Dispatches multiple events
private:

	void setEvent(Evnt ev, int worm);				// Sets the event but it does not activate it.
	void dispatchEvent(Evnt ev, Stage& stage, int wormID);		// The actual dispatcher for every single event
	bool moveWorm(int ev, int worm);				// It decides if the key pressed correspond to a given worm
	bool moveWorm1(int ev);
	bool moveWorm2(int ev);

	array<Ev_t, 3>events;	
};

*/
#include <vector>
#include <list>

using namespace std;

class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	void loadController(controller * cont);
	void getEvent();
	bool areThereActiveEvents();
	Ev_t * returnEvent(int * size);
	void HandleEventDispatch(Stage& stage);
	void removeEvent(list<Ev_t>::iterator it);
	list<Ev_t> events;
private:
	void displatchEvent(Ev_t& ev, Stage& stage);
	vector<controller *> controllers;

};
