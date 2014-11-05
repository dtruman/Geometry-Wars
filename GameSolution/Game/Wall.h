#ifndef WAL
#define WAL

#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix3D.h"
#include <Core.h>

const unsigned int NUM_POINTS = 4;

class Wall
{
public:
	void wallDraw(Core::Graphics&);
	Vector3D wallColl(Matrix3D,Vector3D);
	bool collisionCheck(Matrix3D,int);
};

#endif