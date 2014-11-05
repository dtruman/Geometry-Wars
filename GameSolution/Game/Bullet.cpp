#include "Bullet.h"

Vector3D bulShape[]=
{
	Vector3D(-2.5,7.5,0),
	Vector3D(-2.5,5,0),
	Vector3D(2.5,5,0),
	Vector3D(2.5,7.5,0),
	Vector3D(2.5,5,0)
};
Vector3D trackPos;
Vector3D trackMouse;
Vector2D n1;
float timesDrawn=1;

void Bullet::drawBullet(Core::Graphics& g,Vector3D bulPos,Vector3D MP)
{
	bulSpeed=20;
	for(unsigned int i=0; i < NUM_BULLETSHAPE; i++)
	{
		const Vector3D& v1=bulPos+bulShape[i];
		const Vector3D& v2=bulPos+bulShape[(i+1)%NUM_BULLETSHAPE];

		g.DrawLine(v1.x,v1.y,v2.x,v2.y);
	}
	timesDrawn=1;
	trackPos=bulPos;
	trackMouse=MP;
	timesDrawn++;
};

void Bullet::fBulletDraw(Core::Graphics& g)
{
	n1=normalize(Vector2D(trackMouse.x,trackMouse.y)-Vector2D(trackPos.x,trackPos.y));
	Vector3D bNormal=Vector3D(n1.x,n1.y,0);
	for(unsigned int i=0; i < NUM_BULLETSHAPE; i++)
	{
		const Vector3D& v1=(trackPos+(bNormal*timesDrawn*bulSpeed))+bulShape[i];
		const Vector3D& v2=(trackPos+(bNormal*timesDrawn*bulSpeed))+bulShape[(i+1)%NUM_BULLETSHAPE];

		g.DrawLine(v1.x,v1.y,v2.x,v2.y);
	}
	timesDrawn++;
};