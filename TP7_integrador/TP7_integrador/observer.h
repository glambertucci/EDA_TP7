#pragma once

#include <string>

#define NETOBSNAME "networkobs"
#define STAGEOBSNAME "stageobs"


class observer
{
public:
	virtual void update(void* put) = 0;
	virtual std::string getName() = 0;
};

