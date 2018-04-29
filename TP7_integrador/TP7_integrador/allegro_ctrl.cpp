#include "allegro_ctrl.h"
#define Wid 1
Evnt trasformAllegroEvents(int key)
{
	Evnt ev = NOEVENT;
	switch (key)
	{
	case ALLEGRO_KEY_LEFT:
	case ALLEGRO_KEY_A:
		ev = LEFT_EV;
		break;
	case ALLEGRO_KEY_RIGHT:
	case ALLEGRO_KEY_D:
		ev = RIGHT_EV;
		break;
	case ALLEGRO_KEY_UP:
	case ALLEGRO_KEY_W:
		ev = JUMP_EV;
		break;
	case ALLEGRO_KEY_ESCAPE:
		ev = QUIT_EV;
		break;
	}
	return ev;
}

allegro_ctrl::allegro_ctrl(ALLEGRO_EVENT_QUEUE * eq_)
{
	eq = eq_;
}

void * allegro_ctrl::get_event(void * data)
{
	ev[0].deactivate();
	ev[1].deactivate();

	ALLEGRO_EVENT alEv;

	int * size = (int *)data;

	if (al_get_next_event(eq, &alEv)) {

		switch (alEv.type) {
		case ALLEGRO_EVENT_KEY_DOWN:

			if (alEv.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				ev[2].activate();
				ev[2].Event = QUIT_EV;
			}
			else
				if (!ev[0].active && validKey(alEv.keyboard.keycode) && !ev[0].timerExist())
					setEvent(trasformAllegroEvents(alEv.keyboard.keycode), Wid);
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (ev[0].timerExist() && ev[0].Event == trasformAllegroEvents(alEv.keyboard.keycode)) {
				if (!ev[0].timerGreaterThan(400))
				{
					if (!ev[0].active && ev[0].Event == LEFT_EV) {
						ev[0].Event = FLIP_LEFT_EV;
						ev[0].activate();
					}
					else if (!ev[0].active && ev[0].Event == RIGHT_EV) {
						ev[0].Event = FLIP_RIGHT_EV;
						ev[0].activate();
					}
				}
				break;
		case ALLEGRO_EVENT_TIMER:
			this->setEvent(TIMER_EV);
			ev[1].activate();



			if (!ev[0].active && ev[0].timerExist())
			{
				ev[0].time->stop();
				float time_ = ev[0].time->getTime();
				if (time_ >= 100)
				{
					ev[0].activate();
					ev[0].time->start();
				}
			}



			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ev[1].Event = QUIT_EV;
			break;
			}
		}
	}

	int counter = 0;
	for (int i =0;i<3;i++)
	{
		if (ev[i].active)
			retValue[counter++] = ev[i];
	}
	*size = counter;

	return retValue;
}

bool allegro_ctrl::isThereEvent()
{
	return (ev[0].active || ev[1].active);
}




allegro_ctrl::~allegro_ctrl()
{
}


void allegro_ctrl::setEvent(Evnt evento, unsigned int wormID) {


	if (evento != TIMER_EV) {
		ev[0].Event = evento;
		ev[0].wormID = wormID;
		ev[0].newTimer();
	}
	else
		ev[1].Event = evento;


}

bool allegro_ctrl::validKey(int key) {

	return (key == ALLEGRO_KEY_LEFT || key == ALLEGRO_KEY_RIGHT || key == ALLEGRO_KEY_UP);
}