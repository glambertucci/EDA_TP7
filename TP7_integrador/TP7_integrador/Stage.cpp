#include "Stage.h"
#include "Ev_t.h"
#include "observer.h"
#include "paquete.h"

unsigned int trasnformIDintoPos(unsigned int wormID);

unsigned int trasnformIDintoPos(unsigned int wormID) {
	if (wormID == WORMS)
		return 0;
	else
		return 1;
}

Stage::Stage(netData * net_)
{
	net = net_;
}
netData * Stage::getdata()
{
	return net;
}

Stage::~Stage() //Sacamos a los worms del vector en el cual están almacenados y liberamos esa memoria.
{
	for (int i = 0; i < worms.size(); i++)
		worms.pop_back();
}



void Stage::createWorms(Worm * worm) //Metemos a los worms en su vector correspondiente
{
	this->worms.push_back(*worm);
}

vector<Worm>* Stage::getWorms() //Devuelvo la posición de memoria del vector donde están almacenados los worms.
{
	return &worms;

}

void Stage::destroyWorm(unsigned int wormID) //Destruimos un worm
{
	worms.erase(worms.begin() + trasnformIDintoPos(wormID));
}

void Stage::addObserver(observer * obs) //Agregamos un observer al vector de observers.
{
	observers.push_back(obs);
}

void Stage::wormMoveLeft(unsigned int wormID)
{
	if (worms[trasnformIDintoPos(wormID)].getState() != JUMP_ST) {
		worms[trasnformIDintoPos(wormID)].move(LEFT_DR);
		lastAction = MOVE_LEFT_AT;
	}
}

void Stage::wormMoveRight(unsigned int wormID)
{
	if (worms[trasnformIDintoPos(wormID)].getState() != JUMP_ST) {
		worms[trasnformIDintoPos(wormID)].move(RIGHT_DR);
		lastAction = MOVE_RIGHT_AT;
	}
}

void Stage::wormJump(unsigned int wormID)
{
	worms[trasnformIDintoPos(wormID)].jump();
	lastAction = JUMP_AT;
}

void Stage::wormFlipLeft(unsigned int wormID)
{
	if (worms[trasnformIDintoPos(wormID)].getState() != JUMP_ST) {
		worms[trasnformIDintoPos(wormID)].flipLeft();
		lastAction = FLIP_LEFT_AT;
	}
}

void Stage::wormFlip(unsigned int wormID)
{
	if (worms[trasnformIDintoPos(wormID)].getState() != JUMP_ST) {
		worms[trasnformIDintoPos(wormID)].flip();
		lastAction = FLIP_AT;
	}
}

void Stage::wormFlipRight(unsigned int wormID)
{
	if (worms[trasnformIDintoPos(wormID)].getState() != JUMP_ST) {
		worms[trasnformIDintoPos(wormID)].flipRight();
		lastAction = FLIP_RIGHT_AT;
	}
}

void Stage::refresh()
{
	for (Worm& worm : worms)
		worm.update();

	lastAction = REFRESH_AT;
	update();

}

void Stage::quit() //Pone al miembro "leave" en verdadero, para indicar la finalización del programa.
{
	package_data pckg;
	pckg.header = QUIT;
	string stringConv = compose_pkt(pckg);
	if (this->net->getCurrentMode() == SERVER)
		net->getServer()->sendMessage(stringConv.c_str(), stringConv.length());
	else
		net->getClient()->send_message(stringConv.c_str(), stringConv.length());
	this->leave = true;
}

bool Stage::isOver() //Usado en Ifs para verificar el valor del miembro leave.
{
	return leave;
}

void Stage::update() //Le pido a todo observer en el vector de observers que hagan un update.
{
	for (observer * obs : observers)
		obs->update(this);
}