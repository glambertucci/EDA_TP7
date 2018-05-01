#pragma once
#include "controller.h"
#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>
#include "netData.h"
#include "paquete.h"

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

	std::string getName();

private:

	//parametros de boost para el manejo de IO por internet.
	boost::asio::io_service* IO_handler;
	boost::asio::ip::tcp::socket* socket;
	boost::asio::ip::tcp::resolver* resolver;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::ip::tcp::acceptor* acceptor;

	package_data pckg;
	netData * net;

	bool succesfulHandshake;
	bool timeOut;


	void startConnectionForServer(const char * host);
	void startConnectionForClient();
	void sendMessage();
	bool receiveMessage();

	void renewServerItems();
	void renewClientItems();

	void setEvent(Evnt evento, unsigned int wormID = 0);
	
	Ev_t ev[3];
	Ev_t retValue[3];

	void setName(std::string name);
	std::string controllerType;
};
