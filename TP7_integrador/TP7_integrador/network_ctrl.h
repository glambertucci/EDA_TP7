#pragma once
#include "controller.h"
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include "netData.h"
#include "paquete.h"
#include "client.h"
#include "server.h"
#include <cstdint>

#define PUERTO 15667
#define PUERTO_STR "15667"

Evnt trasformNetworkEvents(char key);

class network_ctrl :
	public controller
{
public:
	network_ctrl(netData * net, std::string name); //Constructor del controller.
	~network_ctrl(); //Destructor del controller.


	void * get_event(void * data);
	void composeAndSend(Ev_t event);
	bool isThereEvent();

	void loadClient(client* cl);
	void loadServer(server* sv);

	std::string getName();

private:

	//---Esto sirve---//
	void setEvent(Evnt evento, uint32_t wormID);

	Ev_t ev[3];
	Ev_t retValue[3];

	void setName(std::string name);
	std::string controllerType;

	package_data pckg;
	netData * net;


	//Info de la red//
	client * netClient;
	server * netServer;
	

};
