#include "obs_network.h"
#include "Stage.h"

void obs_network::update(void * stage) { //sendLocal() para los amigos

	this->events = ((Stage *)stage)->getEventList();


	for (Ev_t ev : * events) { //Reviso cada evento y, si su origen es local, mando una copia por red.
		if (ev.origin == LOCAL && ev.active && (ev.Event != TIMER_EV)) { //Solo envío aquellos eventos locales activos.
			this->composeAndSend(ev);
		}
	}
}

void obs_network::composeAndSend(Ev_t event, void * stage) {

	/*Esta función compone el paquete según el tipo de evento recibido
	y luego lo envía a la otra computadora. */

	Stage * scenario = (Stage *)stage;
	uint32_t Wid = WORMC;

	if (net->getCurrentMode() == CLIENT)
		Wid = WORMC;	
	else
		Wid = WORMS;

	package_data pckg;

	if (event.Event == FLIP_LEFT_EV || event.Event == FLIP_RIGHT_EV) {
		if (shouldFlip()) {
			pckg.header = MOVE;
			pckg.action = 'T';
			pckg.id_worm = Wid;
		}
	}
	else if (event.Event == JUMP_EV) {
		pckg.header = MOVE;
		pckg.action = 'J';
		pckg.id_worm = Wid;
	}
	else if (event.Event == LEFT_EV) {
		pckg.header = MOVE;
		pckg.action = 'I';
		pckg.id_worm = Wid;
	}
	else if (event.Event == RIGHT_EV) {
		pckg.header = MOVE;
		pckg.action = 'D';
		pckg.id_worm = Wid;
	}
	else if (event.Event == QUIT_EV) {
		pckg.header = QUIT;
		pckg.action = NULL;
		pckg.id_worm = NULL;
	}

	if (event.Event != NOEVENT && event.Event != TIMER_EV) { //Si no hay evento o es un evento de timer, no hay motivo para enviarlo.
		string stringConv = compose_pkt(pckg);
		if (this->net->getCurrentMode() == SERVER) {
			net->getServer()->sendMessage(stringConv.c_str(), stringConv.length());
		}
		else
			net->getClient()->send_message(stringConv.c_str(), stringConv.length());
	}
}

bool shouldFlip(void * stage) {

	if(scenario->net)
}