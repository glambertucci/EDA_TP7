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
	void composeAndSend(Ev_t event);
	list<Ev_t> * events; //Vector con los eventos a trabajar.

	// Modificados solo en el constructor //
	netData * net;
};