#ifndef SOLAR
#define SOLAR

#include <Core.h>
#include "Vector3D.h"
#include "Matrix3D.h"

const int NUM_PLANET_SHAPE=12;
const int NUM_PLANET=5;
const float PLANET_SIZE=1;
const float OFFSET=200;

class SolarSystem
{
public:
    void sun(Core::Graphics&, float);
	void planet(Core::Graphics&);
    void planets(Core::Graphics&, int, float, Vector3D, float);
};

#endif