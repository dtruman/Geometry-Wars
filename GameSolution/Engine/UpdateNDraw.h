#ifndef UPDR
#define UPDR

#include <Core.h>
using Core::RGB;
#include "Spaceship.h"
#include "Turret.h"
#include "Wall.h"
#include "SolarSystem.h"
#include "Bullet.h"
#include "arbitObject.h"
#include "Vector3D.h"
#include "ParticleEffect.h"
#include "Timer.h"
#include "Profiler.h"
#include "EnemyShip.h"
#include <sstream>
using std::sprintf;

//const int MAX_COLOR=255;
const int SUN_POS=500;
const int NUM_SUN_PART=200;
const int NUM_COL_PART=50;
const float SUN_PART_SPD=20;
const float COL_PART_SPD=50;
const int STR_TYPE_ONE=1;
const int STR_TYPE_TWO=2;
const int DOWN_DIR=1;
const int UP_DIR=2;
const int RIGHT_DIR=3;
const int LEFT_DIR=4;
const int NO_DIRECTION=5;
const int LIFE_END=1;
const int LIFE_FOREVER=2;
const int MAX_BUL=99;

class UpdateNDraw
{
public:
	Matrix3D position;
	Matrix3D oldPosition;
	Vector3D mousePos;
	void updateMouse();
	void draw(Core::Graphics&);
	void update(float dt);
	Turret tur;
	Wall wal;
	Object obj;
	SolarSystem sol;
	Bullet bul[1000];
	Spaceship sShip;
	int eShipCount;
	float enemySpawner;
	int bulCount;
	int maxBulCount;
	float deltaT;
	float angle;
	bool turnOffArbit;
	bool play;
	void initialize();
	void shutdown();
	void showFrames(Core::Graphics&);
	void destroyEShip(int);
	void UpdateNDraw::gameOver(Core::Graphics&);

	float turUpdTime;
	float sunUpdTime;
	float mouUpdTime;
	float partCheckUpdTime;
	float partUpdTime;
	float sShipUpdTime;
	float objUpdTime;
	
	float sShipDraTime;
	float sunDraTime;
	float turDraTime;
	float bulDraTime;
	float objDraTime;
	float wallDraTime;
	float solDraTime;
	float partDraTime;
};

#endif