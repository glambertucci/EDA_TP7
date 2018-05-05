#include "allegro_ctrl.h"
#include "Worm.h"

Evnt trasformAllegroEvents(int key) //Interpreto los eventos del input de teclado para generar un evento de mi programa.
{
	Evnt ev = NOEVENT;
	switch (key)
	{
	case ALLEGRO_KEY_LEFT:
		ev = LEFT_EV;
		break;
	case ALLEGRO_KEY_RIGHT:
		ev = RIGHT_EV;
		break;
	case ALLEGRO_KEY_UP:
		ev = JUMP_EV;
		break;
	case ALLEGRO_KEY_ESCAPE:
		ev = QUIT_EV;
		break;
	}
	return ev;
}

allegro_ctrl::allegro_ctrl(ALLEGRO_EVENT_QUEUE * eq_, std::string name, netData * netdata){  //Asigno a mi miembro "eq" la dirección de la cola de eventos de Allegro.
	this->eq = eq_;
	setName(name);
	this->net = netdata;
}

void * allegro_ctrl::get_event(void * data)
{
	ev[0].deactivate(); //La posición 0 la uso para input de teclado. La desactivo para recibir una nueva (e indicar que ya se trabajó la anterior)
	ev[1].deactivate(); //La posición 1 la uso para los eventos de timer, además de cerrar por display. La desactivo pues ya se debe haber procesado el evento anterior en caso de que haya habido uno.

	ALLEGRO_EVENT alEv;
	
	WormN Wid = WORMC;

	if (net->getCurrentMode() == CLIENT)
		Wid = WORMC;
	else
		Wid = WORMS;

	int * size = (int *)data;  //Size es la variable que devolveré, que corresponderá a la cantidad de eventos que cargaré y se deberán trabajar.

	if (al_get_next_event(eq, &alEv)) { //Recibo un evento de la cola de eventos y lo guardo en alEv.

		switch (alEv.type) { //Opero según el tipo del evento.
		case ALLEGRO_EVENT_KEY_DOWN:

			if (alEv.keyboard.keycode == ALLEGRO_KEY_ESCAPE) //Si toqué ESC, activaré ev[2], posición exlcusivamente utilizada en este caso para salir del programa.
			{
				ev[2].activate();
				ev[2].Event = QUIT_EV;
				ev[2].origin = LOCAL;
			}
			else
				if (!ev[0].active && validKey(alEv.keyboard.keycode) && !ev[0].timerExist()) //Si la posición 0, correspondiente a input de teclado, está desactivada y tambien lo está su timer...
					setEvent(trasformAllegroEvents(alEv.keyboard.keycode), Wid); //...Entonces interpreto el input y lo introduzco en ev[0].
			break;
		case ALLEGRO_EVENT_KEY_UP: // Si solté una tecla...
			if (ev[0].timerExist() && ev[0].Event == trasformAllegroEvents(alEv.keyboard.keycode)) { //...Si hay un timer y la tecla que solté es la misma que presioné antes...
				if (!ev[0].timerGreaterThan(400)) //...y, además, no se mantuvo presionada el tiempo suficiente... (Recordemos que esta función mata al timer).
				{
					if (!ev[0].active && ev[0].Event == LEFT_EV) { //...Si es la tecla para moverse a la izquierda o derecha, pasaré a mirar a esa dirección, incluso aunque no me mueva en ella. 
						ev[0].Event = FLIP_LEFT_EV;
						ev[0].activate();
						ev[0].origin = LOCAL;
					}
					else if (!ev[0].active && ev[0].Event == RIGHT_EV) {
						ev[0].Event = FLIP_RIGHT_EV;
						ev[0].activate();
						ev[0].origin = LOCAL;
					} 
				}
				break;

		case ALLEGRO_EVENT_TIMER:
			this->setEvent(TIMER_EV);
			ev[1].activate(); //Indico que hubo un evento del timer.



			if (!ev[0].active && ev[0].timerExist()) 
			{
				ev[0].time->stop(); 
				float time_ = ev[0].time->getTime();
				if (time_ >= 100) 
				{
					ev[0].activate(); 
					ev[0].time->start();
				}
			}



			break;
		case  ALLEGRO_EVENT_DISPLAY_CLOSE:
			ev[1].Event = QUIT_EV; //Si cerré el display, guardo en 1 tal evento y luego se trabajará para finalizar el programa.
			ev[1].origin = LOCAL;
			break;
			}
		}
	}

	int counter = 0;
	for (int i =0;i<3;i++) //Me fijo cuantos eventos están activos con un contador.
	{
		if (ev[i].active)
			retValue[counter++] = ev[i]; //Aquellos que estén activos son copiados en retValue para trabajarlos luego.
	}
	*size = counter; //Guardo la cantidad de eventos activos que hay.

	return retValue; //Devuelvo la posición de memoria de retValue, pues este método devuelve un puntero a void.
}

bool allegro_ctrl::isThereEvent()
{
	return (ev[0].active || ev[1].active);
}




allegro_ctrl::~allegro_ctrl()
{
}


void allegro_ctrl::setEvent(Evnt evento, unsigned int wormID) {


	if (evento != TIMER_EV) {
		ev[0].Event = evento;
		ev[0].wormID = wormID;
		ev[0].newTimer();
		ev[0].origin = LOCAL;
	}
	else
		ev[1].Event = evento;


}

bool allegro_ctrl::validKey(int key) {

	return (key == ALLEGRO_KEY_LEFT || key == ALLEGRO_KEY_RIGHT || key == ALLEGRO_KEY_UP);
}



void allegro_ctrl::setName(std::string name) {
	this->controllerType = name;
}

std::string allegro_ctrl::getName() {
	return this->controllerType;
}