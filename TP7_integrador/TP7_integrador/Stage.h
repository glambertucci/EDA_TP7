#pragma once
#include <allegro5\allegro.h>
#include "Worm.h"
#include <vector>
#include "observer.h"
#include <vector>
#include "Ev_t.h"
#include <list>
#include "netData.h"
using namespace std;

typedef enum ActionType
{
	REFRESH_AT, MOVE_LEFT_AT, MOVE_RIGHT_AT, JUMP_AT, FLIP_RIGHT_AT, FLIP_LEFT_AT, FLIP_AT
};

class Stage
{

public:
	Stage(netData * net_);	//Constructor
	~Stage();	//Destructor
	void createWorms(Worm * worm);	//Crea un worm
	vector<Worm> * getWorms();
	void destroyWorm(unsigned int wormID);
	void addObserver(observer * obs);
	void wormMoveLeft(unsigned int wormID); //Métodos referentes al movimiento de los worms.
	void wormMoveRight(unsigned int wormID);
	void wormJump(unsigned int wormID);
	void wormFlipLeft(unsigned int wormID);
	void wormFlipRight(unsigned int wormID);
	void wormFlip(unsigned int wormID);
	void refresh(); //Métodos referentes al estado del programa.
	void quit();
	bool isOver();
	//-----setters-----//
	void setEventList(list<Ev_t> * list) { this->events = list; }
	list<Ev_t> * getEventList() { return this->events; }
	//---Getter--//
	netData * getdata();
private:
	vector<Worm> worms;
	vector<observer *> observers;
	ActionType lastAction;
	list<Ev_t> * events; //Vector con los eventos a trabajar.
	void update();
	netData * net;
	bool leave = false;
};

