#include "Spaceship.h"

/*
	Spaceship Vectors
*/
Vector3D shipPoints[]=
{
	Vector3D(-2.0f, 1.0f,1),
	Vector3D(1.0f, -1.0f,1),
	Vector3D(2.0f, 1.0f,1),
	Vector3D(-1.0f, -1.0f,1)
};

/*
	Handles the drawing of the ship as well as the turret.
*/
void Spaceship::draw(Core::Graphics& g, float angle, Matrix3D position)
{
	const unsigned int NUM_POINTS = sizeof(shipPoints)/sizeof(*shipPoints);
	rotate=index.Rotation(angle);
	for(unsigned int i=0; i < NUM_POINTS; i++)
	{
		const Vector3D& p1=rotate*(shipPoints[i]*SHIP_SIZE);
		const Vector3D& p2=rotate*(shipPoints[(i+1)%NUM_POINTS]*SHIP_SIZE);
		const Vector3D& v1=Vector3D(position.m00,position.m11,0)+p1;
		const Vector3D& v2=Vector3D(position.m00,position.m11,0)+p2;

		g.DrawLine(v1.x,v1.y,v2.x,v2.y);
	}
};

/*
	Handles bounce collision
*/
Matrix3D Spaceship::bounceColl(Matrix3D position, Matrix3D oldPosition)
{
	if(position.m00<=ABSOLUTE_ZERO || position.m00>=ABSOLUTE_FINAL)
	{
			position=oldPosition;
			velocity.x *= BOUNCE_VELOCITY;
	}
	else if(position.m11<=ABSOLUTE_ZERO || position.m11>=ABSOLUTE_FINAL)
	{
		position=oldPosition;
		velocity.y *= BOUNCE_VELOCITY;
	}
	return position;
};

/*
	Handles wrap mode
*/
Matrix3D Spaceship::wrapColl(Matrix3D position)
{
	if(position.m00<=ABSOLUTE_ZERO-SHIP_SIZE)
			position.m00 = ABSOLUTE_FINAL+SHIP_SIZE;
		else if(position.m00>= ABSOLUTE_FINAL+SHIP_SIZE)
			position.m00 = ABSOLUTE_ZERO-SHIP_SIZE;
		else if(position.m11<=ABSOLUTE_ZERO-SHIP_SIZE)
			position.m11 = ABSOLUTE_FINAL+SHIP_SIZE;
		else if(position.m11>=ABSOLUTE_FINAL+SHIP_SIZE)
			position.m11 = ABSOLUTE_ZERO-SHIP_SIZE;

	return position;
};