#include "EnemyShip.h"
#include "Vector2D.h"
#include "Vector3D.h"

Vector3D enemy[]=
{
	Vector3D(0.0f,1.0f,0),
	Vector3D(0.0f,-1.0f,0),
	Vector3D(1.0f,0.0f,0),
	Vector3D(-1.0f,0.0f,0)
};

float enemyAlpha=0;
bool enemyAlive=false;

void EnemyShip::resetEnemyPosition()
{
	Rand rEnemy;
	enemyPosition=Vector3D(rEnemy.randomInRange(0,800),rEnemy.randomInRange(0,800),0);
};

void EnemyShip::enemyDraw(Core::Graphics& g)
{
	const unsigned int NUM_POINTS =4;
	for(unsigned int i=0; i < NUM_POINTS; i++)
	{
		const Vector3D& p1=enemyPosition+(enemy[i]*ENEMY_SIZE);
		const Vector3D& p2=enemyPosition+(enemy[(i+1)%NUM_POINTS]*ENEMY_SIZE);
		g.DrawLine(p1.x,p1.y,p2.x,p2.y);
	}
};

void EnemyShip::enemyUpdate(float dt,Vector3D fightPos)
{
	if(enemyAlive)
	{
		enemyPath=fightPos;

		float enemySpeed=10/Length(Vector2D(enemyPath.x,enemyPath.y)-Vector2D(enemyPosition.x,enemyPosition.y));
		enemyAlpha+=enemySpeed*dt;
		if(enemyAlpha >=1.0f)
		{
			enemyAlpha=0.0f;
		}
		const Vector3D& source=enemyPosition;
		const Vector3D& destination=enemyPath;
		Vector2D enePos=Lerp(Vector2D(source.x,source.y), Vector2D(destination.x,destination.y), enemyAlpha);
		enemyPosition=Vector3D(enePos.x,enePos.y,0);
	}
};