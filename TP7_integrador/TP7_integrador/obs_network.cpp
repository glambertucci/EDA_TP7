#include "obs_network.h"

void obs_network::sendLocal() {
											//Esta es la llamada a la funcion que requiere al vector de comtrollers
	if (network_ctrl * cont = (network_ctrl *)searchForController(NETWORKCONT)) { //Busco si existe un controlador de red y, si no, no ejecuto esta porci�n del programa.
		for (Ev_t ev : events) { //Reviso cada evento y, si su origen es local, mando una copia por red.
			if (ev.origin == LOCAL && ev.active) { //Solo env�o aquellos eventos locales activos.
				cont->composeAndSend(ev);
			}
		}
	}
}

controller * obs_network::searchForController(std::string controllerName) {
	for (controller * cont : controllers) {
		if (cont->getName() == controllerName) {
			return cont;
		}
	}
	return NULL;
}

void obs_network::update(void) {

}