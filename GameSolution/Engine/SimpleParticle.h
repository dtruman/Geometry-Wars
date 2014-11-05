#ifndef SP
#define SP

#include "Vector2D.h"
#include "Core.h"
using Core::RGB;


class SimpleParticle
{
public:
	Vector2D position;
	Vector2D velocity;
	float lifeTime;
	float type;
	RGB color;
	RGB originalColor;
};

#endif