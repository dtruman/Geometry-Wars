#ifndef M2D
#define M2D
#include "Vector2D.h"

struct Matrix2D
{
	float m00;
	float m01;
	float m10;
	float m11;
	Matrix2D(const Vector2D one=Vector2D(1,0), const Vector2D two=Vector2D(0,1))
	{
		m00=one.x; m01=one.y;
		m10=two.x; m11=two.y;
	}

	Matrix2D Matrix2D::Rotation(float angle);
	Matrix2D Matrix2D::Scale(float scale);
	Matrix2D Matrix2D::ScaleX(float scale);
	Matrix2D Matrix2D::ScaleY(float scale);
};

Matrix2D operator*(const Matrix2D& m1, const Matrix2D& m2);
Vector2D operator*(const Matrix2D& m1, const Vector2D v1);

#endif