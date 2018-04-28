#include <allegro5\allegro.h>
#include <vector>
#include "Timer.h"
#include "Stage.h"
<<<<<<< HEAD
#include <list>
#include "controller.h"
#include "allegro_ctrl.h"
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
	list<Ev_t> events;
=======

using namespace std;


// Este enum tiene todos los eventos posibles que puede recibir el programa. Si se quiere usar este EventHandler en otro programa solo habraiq eu cambiar 
// esta parte y un poco del codigo en el .cpp
typedef enum Evnt {
	NOEVENT, LEFT_EV, RIGHT_EV, JUMP_EV, TIMER_EV, QUIT_EV, FLIP_LEFT_EV, FLIP_RIGHT_EV
};

//Esta estructura es el evento que obtenes. Tiene lugar para almacenar el evento actual y el evento anterior, un puntero a timer y tambien te dice si esta
// activo o no el evento. Tiene funciones para manejar tanto los eventos como el timer

typedef struct {
	Evnt Event;
	Evnt lastEv;
	Timer * time;
	bool active;
	int keycode;
	bool keyPressed = true;

	void activate() {
		if (Event == NOEVENT)
			Event = lastEv;
		active = true;
	}
	void deactivate() {
		active = false;
		lastEv = Event;

	}
	void newTimer() {
		time = new Timer();
	}
	bool timerExist() {
		return time != NULL;
	}

	void killTimer() {
		delete time;
		time = NULL;
	}
	// Esta funcion mata al time despues de ser utilizada. CUIDADO
	bool timerGreaterThan(float ms)
	{
		bool retValue = false;
		time->stop();
		if (time->getTime() >= ms)
			retValue = true;
		killTimer();

		return retValue;
	}
}Ev_t;

class EventHandler {
public:
	EventHandler();

	bool getEvent(ALLEGRO_EVENT_QUEUE *  eq);		// Gets the event from the event queue and/or other mediums not yet implemented
	bool isThereEvent();							// Checks if there is an active event
	void handleEventDispatcher(Stage& stage);		// Dispatches multiple events
>>>>>>> parent of 50e3149... Leer descripcion
private:
	void displatchEvent(Ev_t& ev, Stage& stage);
	vector<controller *> controllers;

<<<<<<< HEAD
=======
	void setEvent(Evnt ev, int worm);				// Sets the event but it does not activate it.
	void dispatchEvent(Evnt ev, Stage& stage, int wormID);		// The actual dispatcher for every single event
	bool moveWorm(int ev, int worm);				// It decides if the key pressed correspond to a given worm
	bool moveWorm1(int ev);
	bool moveWorm2(int ev);

	array<Ev_t, 3>events;
>>>>>>> parent of 50e3149... Leer descripcion
};

