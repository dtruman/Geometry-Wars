#ifndef PE
#define PE

#include "SimpleParticle.h"
#include "Color.h"
#include "Rand.h"
#include <Core.h>

const int DIM_LIFE=1;
const int CONTINUE_LIFE=2;
const double END_LIFE=0.0000000001;
const double RESET_LIFE=0.2;

class ParticleEffect
{
	SimpleParticle *particles;
	int numParticles;
	int particleSiz;
	int lifeType;
	Rand myRand;
	Colorness colorness;
	Vector2D originalPos;
public:
	ParticleEffect(Vector2D origin, int numberParticles, RGB color, float speed, int streamType, int dirType, int LT)
	{
		originalPos=origin;
		numParticles=numberParticles;
		particles=new SimpleParticle[numParticles];
		lifeType=LT;
		for(int i=0; i<numParticles; i++)
		{
			particles[i].type=myRand.randomInRange(1,2);
			particles[i].position=origin;
			if(streamType==1)
			{
				particles[i].velocity=myRand.randomUnitVector()*myRand.randomInRange(1,speed);
			}
			else if(streamType==2)
			{
				if(dirType==1)
					particles[i].velocity=Vector2D(myRand.randomInRange(-2,2), 3)*myRand.randomInRange(1,speed);
				else if(dirType==2)
					particles[i].velocity=Vector2D(myRand.randomInRange(-2,2), -3)*myRand.randomInRange(1,speed);
				else if(dirType==3)
					particles[i].velocity=Vector2D(3, myRand.randomInRange(-2,2))*myRand.randomInRange(1,speed);
				else if(dirType==4)
					particles[i].velocity=Vector2D(-3, myRand.randomInRange(-2,2))*myRand.randomInRange(1,speed);
			}
			particles[i].color=colorness.varyColor(color,100);
			particles[i].lifeTime=myRand.randomInRange(1,5);
			particles[i].originalColor=particles[i].color;
		}
	};
	bool updateParticle(float);
	void drawParticle(Core::Graphics&);
};

#endif