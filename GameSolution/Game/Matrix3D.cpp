#include "Matrix3D.h"
#include <math.h>

Matrix3D Matrix3D::Rotation(float angle)
{
	return Matrix3D(Vector3D(cos(angle),-sin(angle),0),Vector3D(sin(angle),cos(angle),0),Vector3D(0,0,1));
};

Matrix3D Matrix3D::Scale(float scale)
{
	return Matrix3D(Vector3D(scale,0,0),Vector3D(0,scale,0),Vector3D(0,0,1));
};

Matrix3D Matrix3D::ScaleX(float scale)
{
	return Matrix3D(Vector3D(scale,0,0),Vector3D(0,1,0),Vector3D(0,0,1));
};

Matrix3D Matrix3D::ScaleY(float scale)
{
	return Matrix3D(Vector3D(1,0,0),Vector3D(0,scale,0),Vector3D(0,0,1));
};

Matrix3D Matrix3D::Translation(float x, float y)
{
	return Matrix3D(Vector3D(1,0,x),Vector3D(0,1,y),Vector3D(0,0,1));
};

Matrix3D Matrix3D::Translation(const Vector3D& t)
{
	return Matrix3D(Vector3D(1,0,t.x),Vector3D(0,1,t.y),Vector3D(0,0,1));
};

Matrix3D operator*(const Matrix3D& m1,const Matrix3D& m2)
{
	Vector3D v1=Vector3D(m1.m00*m2.m00+m1.m01*m2.m10+m1.m02*m2.m20,m1.m00*m2.m01+m1.m01*m2.m11+m1.m02*m2.m21,m1.m00*m2.m02+m1.m01*m2.m12+m1.m02*m2.m22);

	Vector3D v2=Vector3D(m1.m10*m2.m00+m1.m11*m2.m10+m1.m12*m2.m20,m1.m10*m2.m01+m1.m11*m2.m11+m1.m12*m2.m21,m1.m10*m2.m02+m1.m11*m2.m12+m1.m12*m2.m22);

	Vector3D v3=Vector3D(m1.m20*m2.m00+m1.m21*m2.m10+m1.m22*m2.m20,m1.m20*m2.m01+m1.m21*m2.m11+m1.m22*m2.m21,m1.m20*m2.m02+m1.m21*m2.m12+m1.m22*m2.m22);
	return Matrix3D(v1,v2,v3);
}

Vector3D operator*(const Matrix3D& m1, const Vector3D& v1)
{
	return Vector3D(m1.m00*v1.x+m1.m01*v1.y+m1.m02*v1.z,m1.m10*v1.x+m1.m11*v1.y+m1.m12*v1.z,m1.m20*v1.x+m1.m21*v1.y+m1.m22*v1.z);
}