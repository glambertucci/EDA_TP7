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
		break;
	case 'T':
		ev = FLIP_EV;
		break;
	}
	return ev;
}

network_ctrl::network_ctrl(netData * net, std::string name)
{
	this->net = net;
	this->setName(name);
}



network_ctrl::~network_ctrl()
{
}




void * network_ctrl::get_event(void * data) {

	ev[0].deactivate(); //La posición 0 la uso para input de teclado. La desactivo para recibir una nueva (e indicar que ya se trabajó la anterior)
	ev[1].deactivate(); //La posición 1 la uso para los eventos de timer, además de cerrar por display. La desactivo pues ya se debe haber procesado el evento anterior en caso de que haya habido uno.

	
	int * size = (int *)data;  //Size es la variable que devolveré, que corresponderá a la cantidad de eventos que cargaré y se deberán trabajar.
	
	std::string input = ERR_STR;
	
	if (this->net->getCurrentMode() == SERVER) {
		input = this->netServer->receiveMessage();
	}
	else {
		input = this->netClient->receiveMessage();
	}

	if (input != ERR_STR) { //Si recibi un paquete exitósamente, usaré su contenido para mover al segundo worm.

		if(input != NOPACKAGE)
		{
		decompose_data(input, pckg);

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

void network_ctrl::setEvent(Evnt evento, uint32_t wormID) {


	if (evento == FLIP_EV) {
		ev[0].Event = evento;
		ev[0].wormID = wormID;
		ev[0].newTimer();
		ev[0].origin = EXTERN;
	}

}

bool network_ctrl::isThereEvent() {

	return (ev[0].active || ev[1].active);

}

void network_ctrl::setName(std::string name) {
	this->controllerType = name;
}

std::string network_ctrl::getName() {
	return this->controllerType;
}

//void network_ctrl::composeAndSend(Ev_t event) {
//
//	/*Esta función compone el paquete según el tipo de evento recibido
//	y luego lo envía a la otra computadora. */
//
//	if (event.Event == FLIP_LEFT_EV || event.Event == FLIP_RIGHT_EV) {
//		pckg.er = MOVE;
//		pckg.action = 'T';
//		pckg.id_worm = Wid2;
//	}
//	else if (event.Event == JUMP_EV) {
//		pckg.header = MOVE;
//		pckg.action = 'J';
//		pckg.id_worm = Wid2;
//	}
//	else if (event.Event == LEFT_EV) {
//		pckg.header = MOVE;
//		pckg.action = 'D';
//		pckg.id_worm = Wid2;
//	}
//	else if (event.Event == RIGHT_EV) {
//		pckg.header = MOVE;
//		pckg.action = 'I';
//		pckg.id_worm = Wid2;
//	}
//	else if (event.Event == QUIT_EV) {
//		pckg.header = QUIT;
//		pckg.action = NULL;
//		pckg.id_worm = NULL;
//	}
//
//	if (event.Event != NOEVENT && event.Event != TIMER_EV) { //Si no hay evento o es un evento de timer, no hay motivo para enviarlo.
//		
//		string stringConv = compose_pkt(pckg);
//		if (this->net->getCurrentMode() == SERVER) {
//			netServer->sendMessage( stringConv.c_str(), stringConv.length());
//		}
//		else
//			netClient->send_message( stringConv.c_str(), stringConv.length());
//	}
//}

void network_ctrl::loadServer(server * sv)
{
	this->netServer = sv;

}

void network_ctrl::loadClient(client * cl)
{
	this->netClient = cl;
}
