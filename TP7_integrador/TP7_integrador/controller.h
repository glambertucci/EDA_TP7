#pragma once
#include "Ev_t.h"
class controller
{
public:
	virtual void* get_event(void * data) = 0;
};

