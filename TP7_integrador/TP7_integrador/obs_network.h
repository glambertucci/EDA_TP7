#pragma once

#include "observer.h"
#include "network_ctrl.h"


class obs_network :public::observer {
public:
	obs_network(netData * netObj) {
		this->net = netObj;
	}

	void update(void * stage);
	//-----setters-----//
	void setEventList(list<Ev_t> * list) { this->events = list; }



private:
	void composeAndSend(Ev_t event, void * stage);
	list<Ev_t> * events; //Vector con los eventos a trabajar.
	bool shouldFlip(Ev_t ev, void * stage);


	// Modificados solo en el constructor //
	netData * net;
};