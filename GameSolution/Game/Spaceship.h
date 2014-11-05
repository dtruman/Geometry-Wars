#ifndef Ship
#define Ship
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Matrix3D.h"
#include "Vector3D.h"
#include "Core.h"

const int ABSOLUTE_ZERO=0;
const int ABSOLUTE_FINAL=800;
const float SHIP_START=400;
const float SHIP_SIZE=10;
const float SPEED=100;
const float BOUNCE_VELOCITY=-1;

class Spaceship
{
public:
	Matrix3D rotate;
	Matrix3D index;
	Vector3D velocity;
	void draw(Core::Graphics&, float, Matrix3D);
	Matrix3D bounceColl(Matrix3D, Matrix3D);
	Matrix3D wrapColl(Matrix3D);
};

#endif