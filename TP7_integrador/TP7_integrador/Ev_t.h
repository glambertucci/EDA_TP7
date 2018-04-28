#pragma once
#include "EventHandler.h"

typedef enum Evnt {
	NOEVENT, LEFT_EV, RIGHT_EV, JUMP_EV, TIMER_EV, QUIT_EV, FLIP_LEFT_EV, FLIP_RIGHT_EV
};


typedef struct {
	Evnt Event;
	Evnt lastEv;
	Timer * time;
	bool active;
	unsigned int wormID;
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
