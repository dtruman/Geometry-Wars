#ifndef V3D
#define V3D

struct Vector3D
{
	float x;
	float y;
	float z;

	Vector3D(float x=0, float y=0, float z=0) :x(x), y(y), z(z) {}

	operator float*()
	{
		return &x;
	}
};

Vector3D operator+(const Vector3D& left, const Vector3D& right);
Vector3D operator*(const Vector3D& left, float scalar);
Vector3D operator*(const Vector3D& op, const Vector3D& victim);

#endif