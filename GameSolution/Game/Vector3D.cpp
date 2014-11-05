#include "Vector3D.h"

Vector3D operator+(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(left.x+right.x, left.y+right.y,left.z+right.z);
}
Vector3D operator*(const Vector3D& left, float scalar)
{
	return Vector3D(scalar*left.x, scalar*left.y, scalar*left.z);
}