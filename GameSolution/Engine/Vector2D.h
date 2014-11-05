#ifndef V2D
#define V2D
#include <iostream>

struct Vector2D
{
	float x;
	float y;

	Vector2D(float x=0, float y=0) :x(x), y(y) {}

	operator float*()
	{
		return &x;
	}
};

Vector2D perpCW(Vector2D v1);

Vector2D perpCCW(Vector2D v1);

Vector2D normalize(Vector2D v1);

Vector2D Lerp(Vector2D v1, Vector2D v2, float B);

float Dot(Vector2D v1, Vector2D v2);

float Length(Vector2D v1);

float LengthSquared(Vector2D v1);

float Cross(Vector2D v1, Vector2D v2);

Vector2D operator/(Vector2D v1,float length);

Vector2D operator+(const Vector2D& left, const Vector2D& right);

Vector2D operator-(const Vector2D& left, const Vector2D& right);

Vector2D operator*(float scalar, const Vector2D& right);

Vector2D operator*(const Vector2D& left, float scalar);

Vector2D operator*(const Vector2D& op, const Vector2D& victim);

std::ostream& operator<<(std::ostream& stream, const Vector2D& right);

#endif