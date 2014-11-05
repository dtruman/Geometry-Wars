#include "SolarSystem.h"

Vector3D sunCoord=Vector3D(500,500,1);
Matrix3D rotateSol;
Vector3D transSol;
Matrix3D indexSol=(Vector3D(1,0,0),Vector3D(0,1,0),Vector3D(0,0,1));
float angleRot[5];

Vector3D planetShape[]=
{
    Vector3D(-5,20),
    Vector3D(5,20),
    Vector3D(10,10),
    Vector3D(20,5),
    Vector3D(20,-5),
    Vector3D(10,-10),
    Vector3D(5,-20),
    Vector3D(-5,-20),
    Vector3D(-10,-10),
    Vector3D(-20,-5),
    Vector3D(-20,5),
    Vector3D(-10,10)
};
	
void SolarSystem::sun(Core::Graphics& g, float dt)
{
   for(unsigned int i=0; i < NUM_PLANET_SHAPE; i++)
	{
		const Vector3D& p1=sunCoord+(planetShape[i]*2);
		const Vector3D& p2=sunCoord+(planetShape[(i+1)%NUM_PLANET_SHAPE]*2);

		g.DrawLine(p1.x,p1.y,p2.x,p2.y);
	}
   planets(g,NUM_PLANET,PLANET_SIZE,sunCoord,dt);
};

void SolarSystem::planets(Core::Graphics& g, int planetNum, float planetSiz, Vector3D newCoord, float dt)
{
	transSol=Vector3D(OFFSET/planetSiz,0,0);
    rotateSol=indexSol.Rotation(angleRot[planetNum]);
	Vector3D fCoord=(rotateSol*transSol)+newCoord;
	for(unsigned int i=0; i < NUM_PLANET_SHAPE; i++)
	{
		const Vector3D& v1=fCoord+Vector3D(planetShape[i].x/planetSiz,planetShape[i].y/planetSiz,1);
		const Vector3D& v2=fCoord+Vector3D(planetShape[(i+1)%NUM_PLANET_SHAPE].x/planetSiz,planetShape[(i+1)%NUM_PLANET_SHAPE].y/planetSiz,1);

		g.DrawLine(v1.x,v1.y,v2.x,v2.y);
	}
	angleRot[planetNum]+=dt*planetNum;
    if(planetNum>0)
		planets(g,planetNum-1, planetSiz+1, fCoord, dt);
};