#ifndef SET
#define SET

#include "UpdateNDraw.h"
#include <Core.h>

UpdateNDraw gameStuff;
bool startGame=false;

bool MeUpdateFn(float dt)
{
	if(startGame && gameStuff.play)
	{
		gameStuff.update(dt);
	}
	return false;
};

void MeDrawFn(Graphics& graphics)
{
	if(!startGame)
	{
		gameStuff.play=true;
		if(Core::Input::IsPressed('G'))
		{
			startGame=false;
		}
		else if(Core::Input::IsPressed('H'))
		{
			startGame=true;
		}
		graphics.DrawString(250,250, "To play the game press H\nTo turn use the Left and Right arrow keys.\nTo move use the Up and Down arrow keys.\n Left click on screen to shoot in direction of mouse pointer.\nPress Q to activate bounce collision. \nPress W to activate wrap collision.\nPress E to activate arbitrary collision,\n E also resets position.\n Colliding with a wall or window side will create a particle effect.\n Enemies spawn in random positions every 5 seconds!!!!!");
	}
	else if(gameStuff.play)
	{
		graphics.DrawString(2,2,"To observe update profiler information in game, press I.\n To observe draw profiler information in game press O.");
		gameStuff.draw(graphics);
	}
	else
	{
		gameStuff.gameOver(graphics);
	}
};

#endif