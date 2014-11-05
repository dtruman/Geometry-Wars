#include "Rand.h"

float Rand::randomFloat()
{
	return (float) rand() / RAND_MAX;
};

Vector2D Rand::randomUnitVector()
{
	float angle=TWO_PI*randomFloat();
	return Vector2D(cos(angle),sin(angle));
};

float Rand::randomInRange(float min, float max)
{
	return randomFloat()*(max-min+1)+min;
};