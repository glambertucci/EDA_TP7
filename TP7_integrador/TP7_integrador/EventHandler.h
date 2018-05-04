#include <allegro5\allegro.h>
#include <vector>
#include "Timer.h"
#include "Stage.h"
#include "allegro_ctrl.h"
#include "network_ctrl.h"
#include "Ev_t.h"
#include <vector>
#include <list>

using namespace std;

class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	void loadController(controller * cont); //Carga los controllers en su vector correspondiente.
	void getEvent(); //Busca en los controllers si hay algún evento para recibir.
	bool areThereActiveEvents();
	Ev_t * returnEvent(int * size); 
	void HandleEventDispatch(Stage& stage);

	list<Ev_t> * getEventList() { return &(this->events); }


private:
	void displatchEvent(Ev_t& ev, Stage& stage);
	vector<controller *> controllers; //Vector con los controllers activos, a través de los cuales obtengo eventos.
	list<Ev_t> events; //Vector con los eventos a trabajar.
};
