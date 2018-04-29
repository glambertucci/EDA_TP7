#pragma once
#include <allegro5\allegro.h>
#include "Worm.h"
#include "bitinit.h"
#include <vector>
#include "observer.h"
using namespace std;
/*
class Stage
{
public:
	Stage();
	~Stage();
	void draw();
	void createWorms(info * data);
	void loadImages(const char * stage_, const char * backg_);
	vector<Worm> worms;
private:
	ALLEGRO_BITMAP * stageBitmap;
	ALLEGRO_BITMAP * backgroundBitmap;
};
*/
#include <vector>

using namespace std;

typedef enum ActionType
{
	REFRESH_AT, MOVE_LEFT_AT, MOVE_RIGHT_AT, JUMP_AT, FLIP_RIGHT_AT, FLIP_LEFT_AT
};

class Stage
{
public:
	Stage();
	~Stage();
	void createWorms(Worm * worm);
	vector<Worm> * getWorms();
	void destroyWorm(unsigned int wormID);

	void addObserver(observer * obs);

	void wormMoveLeft(unsigned int wormID);
	void wormMoveRight(unsigned int wormID);
	void wormJump(unsigned int wormID);
	void wormFlipLeft(unsigned int wormID);
	void wormFlipRight(unsigned int wormID);
	void refresh();
	void quit();
	bool isOver();
private:
	vector<Worm> worms;
	vector<observer *> observers;
	ActionType lastAction;
	void update();
	bool leave = false;
};

