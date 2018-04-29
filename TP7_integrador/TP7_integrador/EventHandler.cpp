#include <ctype.h>
#include <vector>
#include "EventHandler.h"
#include <iostream>
#include "Ev_t.h"
#include "allegro_ctrl.h"
using namespace std;


/*
// Transforma eventos de allegro en eventos de mi programa

EventHandler::EventHandler()
{
	for (Ev_t& ev : events)
	{
		ev.deactivate();
		ev.time = NULL;
	}
}

// Explicacion del 'getEvent' :

/*
Esta funcion permite tomar eventos de allegro de forma simultanea, ya que al presionar una tecla, se setea el evento (pero no se activa,
entonces no se ejecuta) y se crea un timer que verifica que pase el tiempo de confirmacion. Cuando llega un evento de timer de allegro,
si no hay eventos activos, pero hay un timer activo, verifica que pase el tiempo necesario para que se confirme que el usuario no apreto
la tecla sin querer (100ms en este caso) y se activa el evento correspondiente.

Por ultimo, cuando se suelta la tecla, se verifica si el tiempo del timer es menor a 100ms y se desruye el timer. Si el tiempo es menor,
entonces va a flipear hacia donde se le indico. Sino, no hace nada.





bool EventHandler::getEvent(ALLEGRO_EVENT_QUEUE * eq)
{
	ALLEGRO_EVENT ev;
	bool quit = false;
	//Tenes que desactivar los eventos cada vez que entras
	al_get_next_event(eq, &ev);


	switch (ev.type)
	{
	case ALLEGRO_EVENT_KEY_DOWN:

		if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			quit = true;		// Hace un evnto de Quit
		else
			for (int i = 0; i < 2; ++i)	// Solo hay un worm
				if (!this->events[i].active && moveWorm(ev.keyboard.keycode, i) && !this->events[i].timerExist())
					setEvent(trasformAllegroEvents(ev.keyboard.keycode), i);

		break;
	case ALLEGRO_EVENT_KEY_UP:

		for (int i = 0; i < 2; ++i)// Solo hay un worm
			if (this->events[i].timerExist() && this->events[i].Event == trasformAllegroEvents(ev.keyboard.keycode)) {
				if (!this->events[i].timerGreaterThan(100)) // Pone este 100 con un define
				{
					if (!this->events[i].active && this->events[i].Event == LEFT_EV) {
						this->events[i].Event = FLIP_LEFT_EV;
						this->events[i].activate();
					}
					else if (!this->events[i].active && this->events[i].Event == RIGHT_EV) {
						this->events[i].Event = FLIP_RIGHT_EV;
						this->events[i].activate();
					}
				}
			}

		break;
	case ALLEGRO_EVENT_TIMER:
		this->setEvent(TIMER_EV, 2);
		this->events[2].activate();	// Este iria en la posicion 1


		for (int i = 0; i < 2; ++i) // Solo hay un worm
			if (!this->events[i].active && this->events[i].timerExist())
			{
				this->events[i].time->stop();
				float time_ = this->events[i].time->getTime();
				if (time_ >= 100)//Hacelo con define
				{
					this->events[i].activate();
					this->events[i].time->start();
				}
			}



		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		quit = true;// HAce evento de Quit
		break;
	}

	if (quit)		// Esto es al pedo. podes hacerlo para cuando haya eventos de Quit
		for (int i = 0; i < 2; i++) // Solo hay un worm
			if (this->events[i].timerExist())
				this->events[i].killTimer();

	// hace un sistema que devuelva un puntero a eventos activos y de alguna forma manda el tamaño del mismo.

	return !quit; // Que devuelva un arreglo de eventos activos.

}

bool EventHandler::isThereEvent()
{
	return this->events[0].active || this->events[1].active || this->events[2].active;
}


// Esta funcion es bastante simple. Yo se que tengo un array de eventos, y que el evento del timer de allegro va ultimo, por lo que paso por todos
// y, si estan activos, los ejecuto y los desactivo
void EventHandler::handleEventDispatcher(Stage& stage)
{
	for (int i = 0; i <this->events.size(); i++)
	{
		if (this->events[i].active)
		{
			dispatchEvent(this->events[i].Event, stage, i);
			this->events[i].deactivate();
		}
	}
}

// Este es el dispatcher, y viene con un wormID integrado, que basicamente es el lugar del worm en el vector

void EventHandler::dispatchEvent(Evnt ev, Stage& stage, int wormID = 0)
{
	switch (ev)
	{
	case LEFT_EV: if (stage.worms[wormID].state == STILL) stage.worms[wormID].move(LEFT); break;
	case RIGHT_EV:if (stage.worms[wormID].state == STILL)stage.worms[wormID].move(RIGHT); break;
	case JUMP_EV:if (stage.worms[wormID].state == STILL)stage.worms[wormID].jump(); break;
	case FLIP_LEFT_EV: if (stage.worms[wormID].state == STILL) stage.worms[wormID].flipLeft(); break;
	case FLIP_RIGHT_EV: if (stage.worms[wormID].state == STILL) stage.worms[wormID].flipRight(); break;
	case TIMER_EV:
		stage.draw();
		for (Worm& worm : stage.worms)
		{
			worm.update();
			worm.draw();
		}
	}

}

void EventHandler::setEvent(Evnt ev, int worm)
{

	this->events[worm].Event = ev;

	if (ev != TIMER_EV)
		this->events[worm].newTimer();
}

bool EventHandler::moveWorm(int ev, int worm)
{
	bool retValue = false;

	switch (worm)
	{
	case 0: retValue = moveWorm1(ev);
		break;
	case 1: retValue = moveWorm2(ev);
		break;
	}
	return retValue;
}

bool EventHandler::moveWorm1(int ev)
{
	return ((ev == ALLEGRO_KEY_LEFT) || (ev == ALLEGRO_KEY_RIGHT) || (ev == ALLEGRO_KEY_UP));
}

bool EventHandler::moveWorm2(int ev)
{
	return ((ev == ALLEGRO_KEY_W) || (ev == ALLEGRO_KEY_A) || (ev == ALLEGRO_KEY_D));
}
*/


EventHandler::EventHandler()
{
}


EventHandler::~EventHandler()
{
}

void EventHandler::loadController(controller * cont)
{
	controllers.push_back(cont);
}

void EventHandler::getEvent()		// El networking tambien tiene que tener un controller que le de eventos. hay que usar herencia con controller
{									//  y que el puntero a void sea un int que te da la cantidad de elementos que hay;
	int size = 0;
	for (controller * controller : controllers) {
		Ev_t * evs = (Ev_t *)controller->get_event(&size);
		for (int i = 0; i < size; i++)
			events.push_back(evs[i]);
	}
}

bool EventHandler::areThereActiveEvents()
{
	bool retValue = false;

	for (Ev_t& ev : events)
		if (ev.active)
			retValue = true;


	return retValue;
}

Ev_t * EventHandler::returnEvent(int * size)
{
	Ev_t retValue[5];
	for (int i = 0; i < 5; i++)
		retValue->deactivate();


	for (int i = 0; i < 5 && !events.empty(); i++) {
		retValue[i] = events.front();
		events.pop_front();
		*size = i + 1;
	}
	return retValue;
}

void EventHandler::displatchEvent(Ev_t & ev, Stage& stage)
{
	switch (ev.Event) {
	case LEFT_EV: stage.wormMoveLeft(ev.wormID); break;
	case RIGHT_EV: stage.wormMoveRight(ev.wormID); break;
	case JUMP_EV: stage.wormJump(ev.wormID); break;
	case FLIP_RIGHT_EV: stage.wormFlipRight(ev.wormID); break;
	case FLIP_LEFT_EV: stage.wormFlipLeft(ev.wormID); break;
	case QUIT_EV: stage.quit(); break;
	case TIMER_EV: stage.refresh();	break;
	}
}


void EventHandler::HandleEventDispatch(Stage& stage)
{
	while (events.size()) {
		displatchEvent(*events.begin(), stage);
		events.pop_front();
	}
}
