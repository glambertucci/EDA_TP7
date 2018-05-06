#pragma once
#include "controller.h"
#include "allegroClass.h"
#include "netData.h"
#include "Worm.h"
#include <cstdint>
Evnt trasformAllegroEvents(int key);

class allegro_ctrl :
	public controller
{
public:
	allegro_ctrl(ALLEGRO_EVENT_QUEUE * eq_, std::string name, mode currMode);
	~allegro_ctrl();

	void * get_event(void * data); //Devuelve eventos de Allegro para transformarlo en eventos del programa.
	bool isThereEvent(); //Busca si hay eventos activos

	std::string getName();

private:
	ALLEGRO_EVENT_QUEUE * eq = NULL;
	bool validKey(int key);
	void setEvent(Evnt evento, uint32_t wormID);
	Ev_t ev[3]; //Tres posiciones para cada tipo de evento: Input - Timer - Quit
	Ev_t retValue[3];
	uint32_t localWorm = WORMC;
	void setName(std::string name); //Privada pues no queremos modificar el identificador en ejecución, solo al crearlo.
	std::string controllerType;
};
