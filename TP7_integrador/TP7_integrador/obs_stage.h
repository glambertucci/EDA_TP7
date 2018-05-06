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
	obs_stage(const char * jumpPath, int jumpSize, const char * walkPath, int walkSize, const char * background, const char * stageBitmap);
	~obs_stage();
	void update(void * data);
private:
	void drawWorm(float x_, float y_, vector<ALLEGRO_BITMAP*>& sprite, int tick, int flag);
	ALLEGRO_BITMAP * background = NULL;
	ALLEGRO_BITMAP * stageBitmap = NULL;
	vector<ALLEGRO_BITMAP *> jump;
	int jumpSize;
	int walkSize;
	vector<ALLEGRO_BITMAP *> walk;

};