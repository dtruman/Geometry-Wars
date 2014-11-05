#include "UpdateNDraw.h"

int bulCount=0;
int maxBulCount=0;
int eShipCount=0;
float enemySpawner=0;
bool turnOffArbit=false;
bool play=true;
float angle=0;
float setColl=1;
Vector3D oldVelocity;
ParticleEffect SunEff(Vector2D((float)SUN_POS,(float)SUN_POS),NUM_SUN_PART, RGB(MAX_COLOR,MAX_COLOR,0),SUN_PART_SPD,STR_TYPE_ONE,NO_DIRECTION,LIFE_FOREVER);
const int MAX_EFFECTS=800;
Timer time;
Timer profileTimer;
Profiler& gProfile=gameProfiler;

std::string turUpd="Turret Update";
std::string sunUpd="Sun Effect Update";
std::string mouUpd="Mouse Update";
std::string partCheckUpd="Check for New Particle Effect Update";
std::string partUpd="Particle Update";
std::string sShipUpd="Spaceship Update";
std::string objUpd="Object Update";
std::string sShipDra="Spaceship Draw";
std::string sunDra="Draw Sun Particles";
std::string turDra="Turret Draw";
std::string partDra="Draw Particle";
std::string bulDra="Bullet Draw";
std::string objDra="Object Draw";
std::string wallDra="Wall Draw";
std::string solDra="Solar System Draw";

ParticleEffect* effectArray[MAX_EFFECTS]={};
EnemyShip eShip[10]={};
unsigned numActiveEffects=0;

void UpdateNDraw::initialize()
{
	gProfile.initialize("GameProfiles.csv");
};

void UpdateNDraw::shutdown()
{
	gProfile.shutdown();
};

void effectUpdate(Vector2D vPosition, int dirType)
{
	if(numActiveEffects < MAX_EFFECTS)
	{
		if(dirType==5)
		{
			ParticleEffect* pEffect=new ParticleEffect(vPosition,NUM_COL_PART,RGB(MAX_COLOR,0,0),COL_PART_SPD,STR_TYPE_ONE, dirType,LIFE_END);
			effectArray[numActiveEffects++]=pEffect;
		}
		else
		{
			ParticleEffect* pEffect=new ParticleEffect(vPosition,NUM_COL_PART,RGB(0,0,MAX_COLOR),COL_PART_SPD,STR_TYPE_TWO, dirType,LIFE_END);
			effectArray[numActiveEffects++]=pEffect;
		}
	}
}

void UpdateNDraw::updateMouse()
{
	mousePos=Vector3D(0.0f+Core::Input::GetMouseX(), 0.0f+ Core::Input::GetMouseY(),0);
};

void UpdateNDraw::draw(Core::Graphics& g)
{
	g.SetColor(RGB(MAX_COLOR,MAX_COLOR,MAX_COLOR));
	profileTimer.Start();
	sShip.draw(g, angle, position);
	profileTimer.Stop();
	gProfile.addEntry(sShipDra.c_str(),profileTimer.Interval());
	sShipDraTime=profileTimer.Interval();

	profileTimer.Start();
	SunEff.drawParticle(g);
	profileTimer.Stop();
	gProfile.addEntry(sunDra.c_str(),profileTimer.Interval());
	sunDraTime=profileTimer.Interval();

	g.SetColor(RGB(MAX_COLOR,MAX_COLOR,MAX_COLOR));
	profileTimer.Start();
	tur.updateTurret(mousePos,position);
	profileTimer.Stop();
	gProfile.addEntry(turUpd.c_str(),profileTimer.Interval());
	turUpdTime=profileTimer.Interval();

	profileTimer.Start();
	tur.drawTurrret(g,position);
	profileTimer.Stop();
	gProfile.addEntry(turDra.c_str(),profileTimer.Interval());
	turDraTime=profileTimer.Interval();

	profileTimer.Start();
	for(unsigned int i=0; i<numActiveEffects; i++)
	{
		if(effectArray[i] != NULL )
			effectArray[i]->drawParticle(g);
	}
	profileTimer.Stop();
	gProfile.addEntry(partDra.c_str(),profileTimer.Interval());
	partDraTime=profileTimer.Interval();

	g.SetColor(RGB(MAX_COLOR,MAX_COLOR,MAX_COLOR));

	profileTimer.Start();
	if(Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		bul[bulCount].drawBullet(g,Vector3D(position.m00,position.m11,position.m22),mousePos);
		bulCount++;
		if(bulCount>=MAX_BUL)
			bulCount=0;
	}
	if(bulCount>maxBulCount)
		maxBulCount=bulCount;

	if(maxBulCount>0)
	{
		for(int i=0; i<maxBulCount; i++)
		{
			bul[i].fBulletDraw(g);
			destroyEShip(i);
		}
	}
	profileTimer.Stop();
	gProfile.addEntry(bulDra.c_str(),profileTimer.Interval());
	bulDraTime=profileTimer.Interval();

	profileTimer.Start();
	obj.objectDraw(g);
	profileTimer.Stop();
	gProfile.addEntry(objDra.c_str(),profileTimer.Interval());
	objDraTime=profileTimer.Interval();

	profileTimer.Start();
	wal.wallDraw(g);
	profileTimer.Stop();
	gProfile.addEntry(wallDra.c_str(),profileTimer.Interval());
	wallDraTime=profileTimer.Interval();

	profileTimer.Start();
	sol.sun(g,deltaT);
	profileTimer.Stop();
	gProfile.addEntry(solDra.c_str(),profileTimer.Interval());
	solDraTime=profileTimer.Interval();

	g.SetColor(RGB(MAX_COLOR,0,0));
	if(eShipCount>0)
	{
		for(int i=0; i<eShipCount; i++)
		{
			eShip[i].enemyDraw(g);
			if(((eShip[i].enemyPosition.x-position.m00)<10 && (eShip[i].enemyPosition.x-position.m00)>(-10)) && ((eShip[i].enemyPosition.y-position.m11)<10) && (eShip[i].enemyPosition.y-position.m11)>(-10))
			{
				play=false;
			}
		}
	}
	g.SetColor(RGB(MAX_COLOR,MAX_COLOR,MAX_COLOR));

	showFrames(g);

	gProfile.newFrame();
};

void UpdateNDraw::update(float dt)
{
	time.Start();
	Vector3D Adjust;
	deltaT=dt;
	//Checks for movement of ship
	if(Core::Input::IsPressed(Core::Input::KEY_RIGHT))
		angle+=dt*1;
	if(Core::Input::IsPressed(Core::Input::KEY_LEFT))
		angle-=dt*1;
	if(Core::Input::IsPressed(Core::Input::KEY_DOWN))
		Adjust.y=dt*SPEED;
	if(Core::Input::IsPressed(Core::Input::KEY_UP))
		Adjust.y=-dt*SPEED;

	//Sets collision type
	if(Core::Input::IsPressed('Q'))
		setColl=1;
	if(Core::Input::IsPressed('W'))
		setColl=2;
	if(Core::Input::IsPressed('E'))
	{
		position=Matrix3D(Vector3D(SHIP_START,0,0),Vector3D(0,SHIP_START,0),Vector3D(0,0,0));
		setColl=3;
	}

	//Doesn't Work!
	profileTimer.Start();
	SunEff.updateParticle(dt);
	profileTimer.Stop();
	gProfile.addEntry(sunUpd.c_str(), profileTimer.Interval());
	sunUpdTime=profileTimer.Interval();

	profileTimer.Start();
	updateMouse();
	profileTimer.Stop();
	gProfile.addEntry(mouUpd.c_str(), profileTimer.Interval());
	mouUpdTime=profileTimer.Interval();

	//Runs collision type depending on setting
	profileTimer.Start();
	if(setColl==1)
	{
		if(position.m00<=ABSOLUTE_ZERO)
		{
			effectUpdate(Vector2D(position.m00,position.m11),RIGHT_DIR);
		}
		else if(position.m00>=ABSOLUTE_FINAL)
		{
			effectUpdate(Vector2D(position.m00,position.m11),LEFT_DIR);
		}
		else if(position.m11<=ABSOLUTE_ZERO)
		{
			effectUpdate(Vector2D(position.m00,position.m11),DOWN_DIR);
		}
		else if(position.m11>=ABSOLUTE_FINAL)
		{
			effectUpdate(Vector2D(position.m00,position.m11),UP_DIR);
		}
		position=sShip.bounceColl(position, oldPosition);
	}
	else if(setColl==3)
	{
		if(wal.wallColl(position,sShip.velocity)==sShip.velocity)
		{
			position=oldPosition;
		}
		oldVelocity=sShip.velocity;
		sShip.velocity=wal.wallColl(position,sShip.velocity);

		for(int i=0; i<4; i++)
		{
			if(sShip.velocity.x>0 && sShip.velocity.x!=oldVelocity.x && wal.collisionCheck(position,i))
			{
				effectUpdate(Vector2D(position.m00,position.m11),RIGHT_DIR);
			}
			else if(sShip.velocity.x<0 && sShip.velocity.x!=oldVelocity.x && wal.collisionCheck(position, i))
			{
				effectUpdate(Vector2D(position.m00,position.m11),LEFT_DIR);
			}
			if(sShip.velocity.y>0 && sShip.velocity.y!=oldVelocity.y && wal.collisionCheck(position, i))
			{
				effectUpdate(Vector2D(position.m00,position.m11),DOWN_DIR);
			}
			else if(sShip.velocity.y<0 && sShip.velocity.y!=oldVelocity.y && wal.collisionCheck(position, i))
			{
				effectUpdate(Vector2D(position.m00,position.m11),UP_DIR);
			}
		}
	}
	profileTimer.Stop();
	gProfile.addEntry(partCheckUpd.c_str(),profileTimer.Interval());
	partCheckUpdTime=profileTimer.Interval();

	if(setColl==2)
	{
		position=sShip.wrapColl(position);
	}

	profileTimer.Start();
	for(unsigned int i=0; i<numActiveEffects; i++)
	{
		if(effectArray[i] != NULL )
			effectArray[i]->updateParticle(dt);
	}

	for(int i=numActiveEffects-1; i>=0; i--)
	{
		if(effectArray[i]->updateParticle(dt))
		{
			delete effectArray[i];
			for(unsigned j=i; j<numActiveEffects-1; j++)
			{
				effectArray[j] = effectArray[j+1];
			}
			numActiveEffects--;
		}
	}
	profileTimer.Stop();
	gProfile.addEntry(partUpd.c_str(), profileTimer.Interval());
	partUpdTime=profileTimer.Interval();

	enemySpawner+=dt;

	if(enemySpawner>=2.5f)
	{
		if(eShipCount==9)
			eShipCount=0;
		eShip[eShipCount].resetEnemyPosition();
		eShip[eShipCount].enemyAlive=true;
		enemySpawner=0;
		
		eShipCount++;
	}
	for(int i=0; i<=eShipCount; i++)
	{
		eShip[i].enemyUpdate(dt,Vector3D(position.m00,position.m11,position.m22));
	}

	//Keeps track of last position
	oldPosition=position;

	profileTimer.Start();
	//Updates for new position
	const Matrix3D translate=sShip.index.Translation(sShip.velocity);
	const Matrix3D concat=sShip.rotate*translate;
	sShip.velocity = sShip.velocity + concat*Adjust;
	position.m00=position.m00+sShip.velocity.x*dt;
	position.m11=position.m11+sShip.velocity.y*dt;
	profileTimer.Stop();
	gProfile.addEntry(sShipUpd.c_str(), profileTimer.Interval());
	sShipUpdTime=profileTimer.Interval();

	//Updates the object
	profileTimer.Start();
	obj.objectUpdate(dt);
	profileTimer.Stop();
	gProfile.addEntry(objUpd.c_str(), profileTimer.Interval());
	objUpdTime=profileTimer.Interval();
};

void UpdateNDraw::showFrames(Core::Graphics& g)
{
	std::stringstream intervalStream;
	std::stringstream fpsStream;
	std::stringstream showTime;
	time.Stop();
	float interval=time.Interval();
	intervalStream << interval;
	fpsStream << 1/interval;
	std::string s=intervalStream.str();
	std::string beS="Seconds per Frame: ";
	std::string intervalFinal=beS+s;
	g.DrawString(20,750,intervalFinal.c_str());
	std::string e=fpsStream.str();
	std::string beE="Frames per Second: ";
	std::string fpsFinal=beE+e;
	g.DrawString(20,775,fpsFinal.c_str());

	g.SetColor(RGB(255,0,0));
	if(Core::Input::IsPressed('I'))
	{
		showTime << turUpdTime;
		std::string turU=turUpd + ": " + showTime.str();
		showTime.str("");
		showTime << sunUpdTime;
		std::string sunU=sunUpd + ": " + showTime.str();
		showTime.str("");
		showTime << mouUpdTime;
		std::string mouU=mouUpd + ": " + showTime.str();
		showTime.str("");
		showTime << partCheckUpdTime;
		std::string partCheckU=partCheckUpd + ": " + showTime.str();
		showTime.str("");
		showTime << partUpdTime;
		std::string partU=partUpd + ": " + showTime.str();
		showTime.str("");
		showTime << sShipUpdTime;
		std::string sShipU=sShipUpd + ": " + showTime.str();
		showTime.str("");
		showTime << objUpdTime;
		std::string objU=objUpd + ": " + showTime.str();
		showTime.str("");
		std::string final=turU + "\n" + sunU + "\n" + mouU + "\n" + partCheckU + "\n" + partU + "\n" + sShipU + "\n" + objU;
		g.DrawString(2,30,final.c_str());
	}
	else if(Core::Input::IsPressed('O'))
	{
		showTime << sShipDraTime;
		std::string sShipD=sShipDra + ": " + showTime.str();
		showTime.str("");
		showTime << sunDraTime;
		std::string sunD=sunDra + ": " + showTime.str();
		showTime.str("");
		showTime << turDraTime;
		std::string turD=turDra + ": " + showTime.str();
		showTime.str("");
		showTime << bulDraTime;
		std::string bulD=bulDra + ": " + showTime.str();
		showTime.str("");
		showTime << objDraTime;
		std::string objD=objDra + ": " + showTime.str();
		showTime.str("");
		showTime << wallDraTime;
		std::string wallD=wallDra + ": " + showTime.str();
		showTime.str("");
		showTime << solDraTime;
		std::string solD=solDra + ": " + showTime.str();
		showTime.str("");
		showTime << partDraTime;
		std::string partD=partDra + ": " + showTime.str();
		showTime.str("");
		std::string final=sShipD + "\n" + sunD + "\n" + turD + "\n" + bulD + "\n" + objD + "\n" + wallD + "\n" + solD + "\n" + partD;
		g.DrawString(2,30,final.c_str());
	}
	g.SetColor(RGB(255,255,255));
};

void UpdateNDraw::destroyEShip(int counter)
{
	for(int x=eShipCount-1; x>=0; x--)
	{
		float v=bul[counter].timesDrawn;
		float d=bul[counter].bulSpeed;
		if(((bul[counter].trackPos.x+(bul[counter].n1.x*v*d))-eShip[x].enemyPosition.x<10 && (bul[counter].trackPos.x+(bul[counter].n1.x*v*d))-eShip[x].enemyPosition.x>(-10)) && ((bul[counter].trackPos.y+(bul[counter].n1.y*v*d))-eShip[x].enemyPosition.y<10 && (bul[counter].trackPos.y+(bul[counter].n1.y*v*d))-eShip[x].enemyPosition.y>(-10)))
		{
			eShip[x].enemyAlive=false;
			effectUpdate(Vector2D(eShip[x].enemyPosition.x,eShip[x].enemyPosition.y),NO_DIRECTION);
			eShip[x].enemyPosition=Vector3D(1500,1500,0);
		}
	}
};

void UpdateNDraw::gameOver(Core::Graphics& g)
{
	g.DrawString(350,350,"The enemy has boarded you! You have been defeated!");
};