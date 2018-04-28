#include <allegro5\allegro.h>
#include <vector>
#include "Timer.h"
#include "Stage.h"
#include <list>
#include "controller.h"
#include "allegro_ctrl.h"
using namespace std;

class EventHandler
{
public:
	EventHandler();
	~EventHandler();
	void loadController(controller * cont);
	void getEvent();
	bool areThereActiveEvents();
	Ev_t * returnEvent(int * size);
	void HandleEventDispatch(Stage& stage);
	list<Ev_t> events;
private:
	void displatchEvent(Ev_t& ev, Stage& stage);
	vector<controller *> controllers;

};

