#ifndef BUL
#define BUL

#include "Vector3D.h"
#include "Vector2D.h"
#include <Core.h>

const int NUM_BULLETSHAPE=5;

class Bullet
{
	Vector3D trackMouse;
public:
	Vector3D trackPos;
	Vector2D n1;
	float timesDrawn;
	float bulSpeed;
	void drawBullet(Core::Graphics&,Vector3D,Vector3D);
	void fBulletDraw(Core::Graphics&);
};

#endif