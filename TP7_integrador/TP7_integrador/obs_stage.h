#pragma once
#include "observer.h"
#include <vector>
#include <string>
#include "Stage.h"
#include <allegro5\allegro.h>

#define WARMUP 3
#define AIRTIME 36
#define LANDING 43
#define WALKPICS 15
#define WALKFILE "wwalk-F"
#define JUMPPICS 10
#define JUMPFILE "wjump-F"
#define EXT ".png"
#define BACKGROUNDFILE "background.png"
#define STAGEFILE "Scenario.png"

using namespace std;

class obs_stage : public observer
{
public:
	obs_stage(const char * jumpPath, int jumpSize, const char * walkPath, int walkSize, const char * background, const char * stageBitmap, std::string name);
	~obs_stage();
	void update(void * data);

	std::string getName() { return this->obsName; }

private:
	void drawWorm(float x_, float y_, vector<ALLEGRO_BITMAP*>& sprite, int tick, int flag);
	std::string obsName;
	ALLEGRO_BITMAP * background = NULL;
	ALLEGRO_BITMAP * stageBitmap = NULL;
	vector<ALLEGRO_BITMAP *> jump;
	vector<ALLEGRO_BITMAP *> walk;
	int jumpSize;
	int walkSize;

};