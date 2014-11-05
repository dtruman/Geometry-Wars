#ifndef OBJ
#define OBJ

#include <Core.h>
#include "Vector3D.h"

const int NUM_OBJECT_PATH=4;
const int OBJECT_SIZE=20;

class Object
{
public:
	Vector3D objectPosition;
	int destinationObject;
	int sourceObject;
	float objectAlpha;
	void objectDraw(Core::Graphics& g);
	void objectUpdate(float dt);
	void targetNextObjectPath();
};

#endif