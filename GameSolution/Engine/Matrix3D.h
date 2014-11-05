#ifndef M3D
#define M3D

#include "Vector3D.h"

struct Matrix3D
{
	float m00;
	float m01;
	float m02;
	float m10;
	float m11;
	float m12;
	float m20;
	float m21;
	float m22;
	Matrix3D(const Vector3D one=Vector3D(1,0,0), const Vector3D two=Vector3D(0,1,0), const Vector3D three=Vector3D(0,0,1))
	{
		m00=one.x; m01=one.y; m02=one.z;
		m10=two.x; m11=two.y; m12=two.z;
		m20=three.x; m21=three.y; m22=three.z;
	}
	operator float*()
	{
		return &m00;
	}

	Matrix3D Rotation(float angle);
	Matrix3D Scale(float scale);
	Matrix3D ScaleX(float scale);
	Matrix3D ScaleY(float scale);
	Matrix3D Translation(float x, float y);
	Matrix3D Translation(const Vector3D& t);
};

Matrix3D operator*(const Matrix3D& m1,const Matrix3D& m2);
Vector3D operator*(const Matrix3D& m1, const Vector3D& v1);

#endif