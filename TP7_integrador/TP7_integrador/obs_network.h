#pragma once

#include "observer.h"
#include "network_ctrl.h"


class obs_network :public::observer {
public:
	obs_network(netData * netObj, std::string name) {
		this->net = netObj;
		this->obsName = name;
	}
	void update(void * stage);
	void setEventList(list<Ev_t> * list) { this->events = list; }
	std::string getName() { return this->obsName; }

private:
	void composeAndSend(Ev_t event, void * stage);
	list<Ev_t> * events; //Vector con los eventos a trabajar.
	bool shouldFlip(Ev_t ev, void * stage);
	// Modificados solo en el constructor //
	netData * net;
	std::string obsName;
};