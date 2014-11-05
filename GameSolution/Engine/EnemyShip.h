#ifndef ES
#define ES

#include <Core.h>
#include "Vector3D.h"
#include "Rand.h"

const int ENEMY_SIZE=20;

class EnemyShip
{
public:
	Vector3D enemyPosition;
	Vector3D enemyPath;
	bool enemyAlive;
	int destinationObject;
	int sourceObject;
	float objectAlpha;
	float enemyAlpha;
	void resetEnemyPosition();
	void enemyDraw(Core::Graphics& g);
	void enemyUpdate(float dt,Vector3D);
};

#endif