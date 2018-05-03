#pragma once

#include "observer.h"
#include "network_ctrl.h"


class obs_network:public::observer {
public:
	void update(void);

	void sendLocal(void);
private:
	controller * searchForController(std::string controllerType);
	vector<controller *> controllers; //Vector con los controllers activos, a través de los cuales obtengo eventos.
	list<Ev_t> events; //Vector con los eventos a trabajar.
};