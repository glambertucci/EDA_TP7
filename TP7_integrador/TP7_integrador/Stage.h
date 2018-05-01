#pragma once
#include <allegro5\allegro.h>
#include "Worm.h"
#include "bitinit.h"
#include <vector>
#include "observer.h"
#include <vector>

using namespace std;

typedef enum ActionType
{
	REFRESH_AT, MOVE_LEFT_AT, MOVE_RIGHT_AT, JUMP_AT, FLIP_RIGHT_AT, FLIP_LEFT_AT, FLIP_AT
};

class Stage
{

public:
	Stage();	//Constructor
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

private:
	vector<Worm> worms;
	vector<observer *> observers;
	ActionType lastAction;
	void update();
	bool leave = false;
};

