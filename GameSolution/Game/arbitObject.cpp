#include "arbitObject.h"
#include "Vector2D.h"
#include "Vector3D.h"

Vector3D object[]=
{
	Vector3D(0.0f,1.0f,0),
	Vector3D(1.0f,0.0f,0),
	Vector3D(0.0f,-1.0f,0),
	Vector3D(-1.0f,0.0f,0)
};

Vector3D objectPath[]=
{
	Vector3D(200.0f, 300.0f,0),
	Vector3D(300.0f,200.0f,0),
	Vector3D(600.0f, 400.0f,0),
	Vector3D(400.0f, 600.0f,0)
};

Vector3D objectPosition=Vector3D(200.0f, 300.0f,0);
int destinationObject=1;
int sourceObject=0;
int objectAlpha=0;

void Object::objectDraw(Core::Graphics& g)
{
	const unsigned int NUM_POINTS =4;
	for(unsigned int i=0; i < NUM_POINTS; i++)
	{
		const Vector3D& p1=objectPosition+(object[i]*OBJECT_SIZE);
		const Vector3D& p2=objectPosition+(object[(i+1)%NUM_POINTS]*OBJECT_SIZE);
		g.DrawLine(p1.x,p1.y,p2.x,p2.y);
	}
};

void Object::objectUpdate(float dt)
{
	float objectSpeed=300/Length(Vector2D(objectPath[destinationObject].x,objectPath[destinationObject].y)-Vector2D(objectPath[sourceObject].x,objectPath[sourceObject].y));
	objectAlpha+=objectSpeed*dt;
	if(objectAlpha >=1.0f)
	{
		objectAlpha=0.0f;
		targetNextObjectPath();
	}
	const Vector3D& source=objectPath[sourceObject];
	const Vector3D& destination=objectPath[destinationObject];
	Vector2D objPos=Lerp(Vector2D(source.x,source.y), Vector2D(destination.x,destination.y), objectAlpha);
	objectPosition=Vector3D(objPos.x,objPos.y,0);
};

void Object::targetNextObjectPath()
{
	sourceObject=destinationObject;
	destinationObject = (destinationObject+1)%NUM_OBJECT_PATH;
};