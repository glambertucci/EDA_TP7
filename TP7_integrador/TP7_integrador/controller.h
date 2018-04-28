#pragma once
#include "Ev_t.h"
class controller
{
public:
	virtual Ev_t* get_event()=0;
};

