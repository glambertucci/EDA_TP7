#include "Stage.h"
#include "Ev_t.h"
#include "observer.h"
/*
Stage::Stage()
{
	this->backgroundBitmap = NULL;
	this->stageBitmap = NULL;
}


Stage::~Stage()
{
	if (this->backgroundBitmap)
		al_destroy_bitmap(this->backgroundBitmap);
	if (this->stageBitmap)
		al_destroy_bitmap(this->stageBitmap);

	for (int i = 0; i < worms.size(); i++)
		worms.pop_back();
}

void Stage::draw()
{
	al_draw_bitmap(this->backgroundBitmap, 0, 0, 0);
	al_draw_bitmap(this->stageBitmap, 0, 0, 0);
}

void Stage::createWorms(info * data)
{
	this->worms.push_back(Worm(data)); //Implemented with vectors
	this->worms.push_back(Worm(data));
}

void Stage::loadImages(const char * stage_, const char * backg_)
{
	this->backgroundBitmap = al_load_bitmap(backg_);
	this->stageBitmap = al_load_bitmap(stage_);
}
*/

unsigned int trasnformIDintoPos(unsigned int wormID);

unsigned int trasnformIDintoPos(unsigned int wormID) {
	return 0;
}

Stage::Stage()
{

}


Stage::~Stage()
{
	for (int i = 0; i < worms.size(); i++)
		worms.pop_back();
}



void Stage::createWorms(Worm * worm)
{
	this->worms.push_back(*worm);
}

vector<Worm>* Stage::getWorms()
{
	return &worms;
}

void Stage::destroyWorm(unsigned int wormID)
{
	worms.erase(worms.begin() + trasnformIDintoPos(wormID));
}

void Stage::addObserver(observer * obs)
{
	observers.push_back(obs);
}

void Stage::wormMoveLeft(unsigned int wormID)
{
	worms[trasnformIDintoPos(wormID)].move(LEFT_DR);
	lastAction = MOVE_LEFT_AT;
}

void Stage::wormMoveRight(unsigned int wormID)
{
	worms[trasnformIDintoPos(wormID)].move(RIGHT_DR);
	lastAction = MOVE_RIGHT_AT;
}

void Stage::wormJump(unsigned int wormID)
{
	worms[trasnformIDintoPos(wormID)].jump();
	lastAction = JUMP_AT;
}

void Stage::wormFlipLeft(unsigned int wormID)
{
	worms[trasnformIDintoPos(wormID)].flipLeft();
	lastAction = FLIP_LEFT_AT;
}

void Stage::wormFlipRight(unsigned int wormID)
{
	worms[trasnformIDintoPos(wormID)].flipRight();
	lastAction = FLIP_RIGHT_AT;
}

void Stage::refresh()
{
	for (Worm& worm : worms)
		worm.update();

	lastAction = REFRESH_AT;
	update();

}

void Stage::quit()
{
	leave = true;
}

bool Stage::isOver()
{
	return leave;
}

void Stage::update()
{
	for (observer * obs : observers)
		obs->update(this);
}
