#pragma once
#include "Ev_t.h"
#include <string>

#define ALLEGROCONT "allegro"
#define NETWORKCONT "network"

#define Wid 1
#define Wid2 2

class controller
{
public:
	virtual void* get_event(void * data) = 0;
	virtual void setName(std::string name) = 0; //Aqui se define un identificador, el cual deber�a ser �nico para cada controlador, permitiendonos as� acceder a un controlador en espec�fico.
	virtual std::string getName() = 0;
};

