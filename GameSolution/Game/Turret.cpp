#include "Turret.h"

Vector3D turret[]=
{
	Vector3D(-turretLength,turretLength,0),
	Vector3D(-turretLength/2,turretLength,0),
	Vector3D(-turretLength/2,0,0),
	Vector3D(turretLength/2,0,0),
	Vector3D(turretLength/2,turretLength,0),
	Vector3D(turretLength,turretLength,0),
	Vector3D(turretLength,-turretLength,0),
	Vector3D(-turretLength,-turretLength,0)
};

void Turret::drawTurrret(Core::Graphics& g, Matrix3D position)
{
	for(unsigned int i=0; i<TURRET_NUM; i++)
	{
		const Vector3D& p1=Vector3D(position.m00,position.m11,0)+(basisMat*turret[i]);
		const Vector3D& p2=Vector3D(position.m00,position.m11,0)+(basisMat*turret[(i+1)%TURRET_NUM]);
		g.DrawLine(p1.x,p1.y,p2.x,p2.y);
	}
};

void Turret::updateTurret(Vector3D mousePos,Matrix3D position)
{
	Vector2D mouseVector=Vector2D(mousePos.x,mousePos.y)-Vector2D(position.m00,position.m11);
	Vector2D tur=normalize(mouseVector);
	Vector2D turPerp=perpCW(tur);
	normalizedTurLen=Vector3D(tur.x,tur.y,0);
	perp3Tur=Vector3D(turPerp.x,turPerp.y,0);
	basisMat=Matrix3D(perp3Tur,normalizedTurLen,Vector3D(0,0,1));
};