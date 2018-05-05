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

	void * get_event(void * data);
	bool isThereEvent();

	std::string getName();

private:
	ALLEGRO_EVENT_QUEUE * eq = NULL;
	bool validKey(int key);
	void setEvent(Evnt evento, uint32_t wormID);
	Ev_t ev[3];
	Ev_t retValue[3];
	void setName(std::string name); //Privada pues no queremos modificar el identificador en ejecución, solo al crearlo.
	std::string controllerType;
	uint32_t localWorm = WORMC;

};
