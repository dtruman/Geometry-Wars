#include "Matrix2D.h"
#include "Vector2D.h"

Matrix2D Matrix2D::Rotation(float angle)
{
	return (Vector2D(cos(angle),-sin(angle)),Vector2D(sin(angle),cos(angle)));
};
Matrix2D Matrix2D::Scale(float scale)
{
	return (scale*m00,m01,m10,scale*m11);
};
Matrix2D Matrix2D::ScaleX(float scale)
{
	return (scale*m00,m01,m10,m11);
};
Matrix2D Matrix2D::ScaleY(float scale)
{
	return (m00,m01,m10,scale*m11);
};

Matrix2D operator*(const Matrix2D& m1, const Matrix2D& m2)
{
	return Matrix2D(Vector2D((m1.m00*m2.m00+m1.m01*m2.m10),(m1.m00*m2.m01+m1.m01*m2.m11)),Vector2D((m1.m10*m2.m00+m1.m11*m2.m10),(m1.m10*m2.m01+m1.m11*m2.m11)));
}

Vector2D operator*(const Matrix2D& m1, const Vector2D v1)
{
	return Vector2D((m1.m00*v1.x)+(m1.m10*v1.y),(m1.m01*v1.x)+(m1.m11*v1.y));
}