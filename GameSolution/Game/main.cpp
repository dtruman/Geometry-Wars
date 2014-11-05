#include "Engine.h"
#include <Core.h>
using Core::Graphics;
#include "Setup.h"

int main()
{
	gameStuff.initialize();
	gameStuff.position=Matrix3D(Vector3D(SHIP_START,0,0),Vector3D(0,SHIP_START,0),Vector3D(0,0,1));
	Core::Init("Me Window", ABSOLUTE_FINAL, ABSOLUTE_FINAL);
	Core::RegisterUpdateFn(MeUpdateFn);
	Core::RegisterDrawFn(MeDrawFn);
	Core::GameLoop();
	gameStuff.shutdown();
}
