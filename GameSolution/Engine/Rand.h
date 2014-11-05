#ifndef RAN
#define RAN

#include <stdlib.h>
#include "Vector2D.h"

const float TWO_PI=2*3.1415926f;

class Rand
{
public:
	float randomFloat();
	Vector2D randomUnitVector();
	float randomInRange(float min, float max);
};

#endif