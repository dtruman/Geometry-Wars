#ifndef TUR
#define TUR

#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix3D.h"
#include "Core.h"

const int TURRET_NUM=8;
const float turretLength=5;

class Turret
{
public:
	Matrix3D basisMat;
	Vector3D perp3Tur;
	Vector3D normalizedTurLen;
	Vector2D perpTur;
	void drawTurrret(Core::Graphics&, Matrix3D);
	void updateTurret(Vector3D, Matrix3D);
};

#endif