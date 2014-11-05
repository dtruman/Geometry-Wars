#include "Wall.h"

Vector3D wall[]=
{
	Vector3D(400.0f, 50.0f,0),
	Vector3D(750.0f, 400.0f,0),
	Vector3D(400.0f, 750.0f,0),
	Vector3D(50.0f,400.0f,0)
};

void Wall::wallDraw(Core::Graphics& g)
{
	for(unsigned int i=0; i < NUM_POINTS; i++)
	{
		const Vector3D& p1=(wall[i]);
		const Vector3D& p2=(wall[(i+1)%NUM_POINTS]);
		g.DrawLine(p1.x,p1.y,p2.x,p2.y);
	}
};

Vector3D Wall::wallColl(Matrix3D position, Vector3D velocity)
{
	for(int i=0; i<NUM_POINTS; i++)
	{
		if(collisionCheck(position,i))
		{
			Vector2D normal = i+1<NUM_POINTS ? normalize(perpCW(Vector2D(wall[(i+1)].x,wall[(i+1)].y)-Vector2D(wall[i].x,wall[i].y))) : normalize(perpCW(Vector2D(wall[0].x,wall[0].y)-Vector2D(wall[i].x,wall[i].y)));
			Vector2D vel=Vector2D(velocity.x,velocity.y)-(2*((Dot(Vector2D(velocity.x,velocity.y),normal))*normal));
			velocity=Vector3D(vel.x,vel.y,0);
		}
	}
	return velocity;
};

bool Wall::collisionCheck(Matrix3D position, int looker)
{
	Vector2D vectorC=Vector2D(position.m00,position.m11)-Vector2D(wall[looker].x,wall[looker].y);
	Vector2D perpWall=looker+1<4 ? perpCW((Vector2D(wall[looker+1].x,wall[looker+1].y))-Vector2D(wall[looker].x,wall[looker].y)) : perpCW((Vector2D(wall[0].x,wall[0].y))-Vector2D(wall[looker].x,wall[looker].y));
	bool isCollide=false;

	if(Dot(vectorC,perpWall)<0)
		isCollide=true;

	return isCollide;
};