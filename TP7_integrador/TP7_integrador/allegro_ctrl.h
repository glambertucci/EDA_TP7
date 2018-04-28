#pragma once
#include "allegroClass.h"
#include "controller.h"

class Al_ctrl :
	public controller
{
public:
	Al_ctrl(ALLEGRO_EVENT_QUEUE * eq_);
	~Al_ctrl();

	void * getEvent(void * data);
	bool isThereEvent();


private:
	ALLEGRO_EVENT_QUEUE * eq = NULL;
	bool validKey(int key);
	void setEvent(Evnt evento, unsigned int wormID = 0);
	Ev_t ev[2];
};
