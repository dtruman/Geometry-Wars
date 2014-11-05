#ifndef COL
#define COL

#include "Rand.h"
#include "Core.h"
using Core::RGB;

const int MAX_COLOR=255;

class Colorness
{
	int r,g,b;
	Rand myRand;
public:
	RGB varyColor(RGB, int);
	RGB Brightness(RGB, float);
};

#endif