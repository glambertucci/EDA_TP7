#include "network_ctrl.h"
#include <boost/algorithm/string.hpp>
#include <iostream>

Evnt trasformNetworkEvents(char key) //Interpreto los eventos del input de teclado para generar un evento de mi programa.
{
	Evnt ev = NOEVENT;
	switch (key)
	{
	case 'I':
		ev = LEFT_EV;
		break;
	case 'D':
		ev = RIGHT_EV;
		break;
	case 'J':
		ev = JUMP_EV;
	case 'T':
		ev = FLIP_EV;
		break;
	}
	return ev;
}

network_ctrl::network_ctrl(netData * net, std::string name)
{
	this->succesfulHandshake = false;;
	this -> timeOut = false;


	this->IO_handler = new boost::asio::io_service();
	this -> socket = new boost::asio::ip::tcp::socket(*IO_handler);
	this ->acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PUERTO));
	this -> resolver = new boost::asio::ip::tcp::resolver(*IO_handler);

	this->net = net;

	this->setName(name);
/*
	if (this->net->getCurrentMode() == SERVER) {
		startConnectionForServer("127.0.0.1");
	}
	else{
		startConnectionForClient();
	}
	*/
}



network_ctrl::~network_ctrl()
{

	acceptor->close();
	socket->close();
	delete resolver;
	delete acceptor;
	delete socket;
	delete IO_handler;

}


void * network_ctrl::get_event(void * data) {

	ev[0].deactivate(); //La posición 0 la uso para input de teclado. La desactivo para recibir una nueva (e indicar que ya se trabajó la anterior)
	ev[1].deactivate(); //La posición 1 la uso para los eventos de timer, además de cerrar por display. La desactivo pues ya se debe haber procesado el evento anterior en caso de que haya habido uno.


	int * size = (int *)data;  //Size es la variable que devolveré, que corresponderá a la cantidad de eventos que cargaré y se deberán trabajar.
	
	bool correctInput = receiveMessage();

	if (correctInput) { //Si recibi un paquete exitósamente, usaré su contenido para mover al segundo worm.

		switch (pckg.header) { //Opero según el tipo del evento.
		case MOVE:
					this->setEvent(trasformNetworkEvents(pckg.action), pckg.id_worm); //...Entonces interpreto el input y lo introduzco en ev[0]
			break;
		case  QUIT:
			ev[1].Event = QUIT_EV; //Si cerré el display, guardo en 1 tal evento y luego se trabajará para finalizar el programa.
			ev[1].origin = EXTERN;
			break;
			}
		}

	int counter = 0;
	for (int i = 0; i<3; i++) //Me fijo cuantos eventos están activos con un contador.
	{
		if (ev[i].active)
			retValue[counter++] = ev[i]; //Aquellos que estén activos son copiados en retValue para trabajarlos luego.
	}
	*size = counter; //Guardo la cantidad de eventos activos que hay.


	return retValue; //Devuelvo la posición de memoria de retValue, pues este método devuelve un puntero a void.

}

void network_ctrl::setEvent(Evnt evento, unsigned int wormID) {


	if (evento == FLIP_EV) {
		ev[0].Event = evento;
		ev[0].wormID = wormID;
		ev[0].newTimer();
		ev[0].origin = EXTERN;
	}

}


void network_ctrl::composeAndSend(Ev_t event) {

	/*Esta función compone el paquete según el tipo de evento recibido
	y luego lo envía a la otra computadora. */

	if (event.Event == FLIP_LEFT_EV || event.Event == FLIP_RIGHT_EV) {
		pckg.header = MOVE;
		pckg.action = 'T';
		pckg.id_worm = Wid2;
	}
	else if (event.Event == JUMP_EV) {
		pckg.header = MOVE;
		pckg.action = 'J';
		pckg.id_worm = Wid2;
	}
	else if (event.Event == LEFT_EV) {
		pckg.header = MOVE;
		pckg.action = 'D';
		pckg.id_worm = Wid2;
	}
	else if (event.Event == RIGHT_EV) {
		pckg.header = MOVE;
		pckg.action = 'I';
		pckg.id_worm = Wid2;
	}
	else if (event.Event == QUIT_EV) {
		pckg.header = QUIT;
		pckg.action = NULL;
		pckg.id_worm = NULL;
	}

	if (event.Event != NOEVENT && event.Event != TIMER_EV) { //Si no hay evento o es un evento de timer, no hay motivo para enviarlo.
		sendMessage();
	}
}

bool network_ctrl::isThereEvent() {

	return (ev[0].active || ev[1].active);

}

void network_ctrl::sendMessage() {

	size_t len;
	boost::system::error_code error;

	std::string auxString = compose_pkt(this->pckg);

	do
	{
		len = this->socket->write_some(boost::asio::buffer(auxString, strlen(compose_pkt(this->pckg).c_str())), error); //Envío un paquete, transformado al formato correspondiente aceptado por boost.
	} while ((error.value() == WSAEWOULDBLOCK));

	if (error)
		std::cout << "Error while trying to send message. " << error.message() << std::endl;
}

bool network_ctrl::receiveMessage() {

	boost::system::error_code error;

	char buf[sizeof(package_data)];		// Por donde recibiré el input. Tamaño de package_data, ya que todo lo que hago al descomponerlo es acomodarlo en un conjunto de chars, pero ocupa lo mismo.

	bool correctInput = false; 

	size_t len = 0;

	do
	{
		len = socket->read_some(boost::asio::buffer(buf), error);			//leo el input que me envia la otra maquina
		if (!error)
			buf[len] = '\0';					 ///Esto no sé por qué pasa, Tomas lo puso así y el TP funcionaba.		

	} while (error.value() == WSAEWOULDBLOCK);

	std::string auxString;

	if (!error)
		if (len >= (sizeof(package_data))) {			//Copio la cantidad de caracteres que necesito.
			for (int i = 0; i < (sizeof(package_data)); i++)
				auxString[i] = buf[i];							//Cargo el paquete en un string...
		
			decompose_data(auxString, this->pckg); //...Y lo coloco en package data.
			correctInput = checkValidPkgCompos(this->pckg);
		}
		else
			std::cout << "Error while trying to connect to server " << error.message() << std::endl;

	return correctInput;
}


void network_ctrl::renewServerItems() {

	delete socket;
	delete IO_handler;
	delete resolver;

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	resolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

void network_ctrl::renewClientItems() {

	delete acceptor;
	delete socket;
	delete IO_handler;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	IO_handler = new boost::asio::io_service();
	socket = new boost::asio::ip::tcp::socket(*IO_handler);
	acceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
		boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PUERTO));
}


void network_ctrl::setName(std::string name) {
	this->controllerType = name;
}

std::string network_ctrl::getName() {
	return this->controllerType;
}

void network_ctrl::startConnectionForServer(const char * host) {
	try {

		endpoint = resolver->resolve(boost::asio::ip::tcp::resolver::query(host, PUERTO_STR));

		boost::asio::connect(*socket, endpoint);

		socket->non_blocking(true);
	}
	catch (std::exception & e) {
		std::cout << "Error al intentar conectar" << std::endl;
		net->setIfShouldEnd(true);
	}

}


void network_ctrl::startConnectionForClient() {

	renewClientItems();

	acceptor->accept(*socket);

	socket->non_blocking(true);


}