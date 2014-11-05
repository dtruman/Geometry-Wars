#include "ParticleEffect.h"

bool ParticleEffect::updateParticle(float dt)
{
	bool checkLife=false;

	for(int i=0; i<numParticles; i++)
	{
		particles[i].position=particles[i].position+particles[i].velocity*dt;
		particles[i].position=particles[i].position+particles[i].velocity*dt;
		particles[i].lifeTime-=dt;

		if(particles[i].lifeTime<DIM_LIFE)
		{
			particles[i].color=colorness.Brightness(particles[i].color,particles[i].lifeTime);
		}

		if(particles[i].lifeTime<END_LIFE)
		{
			checkLife=true;
		}

		if(particles[i].lifeTime<RESET_LIFE && lifeType==CONTINUE_LIFE)
		{
			particles[i].position=originalPos;
			particles[i].lifeTime=myRand.randomInRange(1,5);
			particles[i].color=particles[i].originalColor;
			checkLife=false;
		}
	}
	return checkLife;
};

void ParticleEffect::drawParticle(Core::Graphics& g)
{
	Vector2D pointA, pointB;
	particleSiz=5;

	for(int i=0; i<numParticles; i++)
	{
		g.SetColor(particles[i].color);
		if(particles[i].type>1 && particles[i].type<2)
		{
			pointA=particles[i].position;
			pointB=particles[i].position+Vector2D(1,0);
			g.DrawLine(pointA.x,pointA.y,pointB.x,pointB.y);
		}
		else if(particles[i].type>2)
		{
			for(int j=0; j<particleSiz; j++)
			{
				pointA=particles[i].position+Vector2D((float)-j,0);
				pointB=particles[i].position+Vector2D(0,(float)j);
				g.DrawLine(pointA.x,pointA.y,pointB.x,pointB.y);
				
				pointA=particles[i].position+Vector2D(0,(float)j);
				pointB=particles[i].position+Vector2D((float)j,0);
				g.DrawLine(pointA.x,pointA.y,pointB.x,pointB.y);

				pointA=particles[i].position+Vector2D((float)j,0);
				pointB=particles[i].position+Vector2D(0,(float)-j);
				g.DrawLine(pointA.x,pointA.y,pointB.x,pointB.y);
				
				pointA=particles[i].position+Vector2D(0,(float)-j);
				pointB=particles[i].position+Vector2D((float)-j,0);
				g.DrawLine(pointA.x,pointA.y,pointB.x,pointB.y);
			}
		}
	}
};