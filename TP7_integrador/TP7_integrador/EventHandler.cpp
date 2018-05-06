#include <ctype.h>
#include <vector>
#include "EventHandler.h"
#include <iostream>
#include "Ev_t.h"
#include "allegro_ctrl.h"
using namespace std;


EventHandler::EventHandler(){}

EventHandler::~EventHandler(){}

void EventHandler::loadController(controller * cont) //Cargo un puntero a controller en el vector correspondiente, para poder acceder a el y obtener eventos.
{
	controllers.push_back(cont);
}

void EventHandler::getEvent()		// El networking tambien tiene que tener un controller que le de eventos. hay que usar herencia con controller
{									//  y que el puntero a void sea un int que te da la cantidad de elementos que hay;
	int size = 0;
	for (controller * controller : controllers) { //Por cada controller, recibo sus eventos y los cargo en la lista de eventos para luego trabajarlos.
		Ev_t * evs = (Ev_t *)controller->get_event(&size);
		for (int i = 0; i < size; i++)
			events.push_back(evs[i]);
	}
}

bool EventHandler::areThereActiveEvents()
{
	bool retValue = false;
	for (Ev_t& ev : events) //Reviso la lista de eventos para ver si hay algún evento activo e informarlo.
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
	case LEFT_EV:  stage.wormMoveLeft(ev.wormID); stage.refresh(); break;
	case RIGHT_EV: stage.wormMoveRight(ev.wormID); stage.refresh(); break;
	case JUMP_EV: stage.wormJump(ev.wormID); stage.refresh(); break;
	case FLIP_RIGHT_EV: stage.wormFlipRight(ev.wormID); stage.refresh(); break;
	case FLIP_LEFT_EV: stage.wormFlipLeft(ev.wormID); stage.refresh(); break;
	case FLIP_EV: stage.wormFlip(ev.wormID); stage.refresh(); break;
	case QUIT_EV: stage.quit(); break;
	case TIMER_EV: stage.refresh();	break;
	}
}


void EventHandler::HandleEventDispatch(Stage& stage)
{
	while (events.size()) { //Mientras queden eventos por trabajar, repetiré el loop.
		displatchEvent(*events.begin(), stage); //Llamo al verdadero dispatcher. Le paso el primer evento de la lista y el escenario.
		events.pop_front(); //Elimino el evento que acabo de trabajar.
	}
}