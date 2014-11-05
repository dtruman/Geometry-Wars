#include <Vector2D.h>
#include <Matrix2D.h>
#include <Matrix3D.h>
#include <iostream>


//Methods Start
Vector2D Lerp(Vector2D v1, Vector2D v2, float B)
{
	return (((1-B)*v1) + (B*v2));
};

Vector2D perpCW(Vector2D v1)
{
	return Vector2D(-v1.y,v1.x);
};

Vector2D perpCCW(Vector2D v1)
{
	return Vector2D(v1.y,-v1.x);
};

Vector2D normalize(Vector2D v1)
{
	return (v1/Length(v1));
};

float Dot(Vector2D v1, Vector2D v2)
{
	return (v1.x*v2.x+v1.y*v2.y);
};

float Length(Vector2D v1)
{
	return sqrt(pow(v1.x,2)+pow(v1.y,2));
};

float LengthSquared(Vector2D v1)
{
	return pow(Length(v1),2);
};

float Cross(Vector2D v1, Vector2D v2)
{
	return (v1.x*v2.y-v1.y*v2.x);
};
//End of Methods


//Define operator overloads
std::ostream& operator<<(std::ostream& stream, const Vector2D& right)
{
	stream << "{" << right.x << "," << right.y << "}";
	return stream;
}

Vector2D operator*(float scalar, const Vector2D& right)
{
	return Vector2D(scalar*right.x, scalar*right.y);
}

Vector2D operator*(const Vector2D& left, float scalar)
{
	return Vector2D(scalar*left.x, scalar*left.y);
}

Vector2D operator/(Vector2D v1,float length)
{
	return Vector2D(v1.x/length, v1.y/length);
}

Vector2D operator+(const Vector2D& left, const Vector2D& right)
{
	return Vector2D(left.x+right.x, left.y+right.y);
}

Vector2D operator-(const Vector2D& left, const Vector2D& right)
{
	return Vector2D(left.x-right.x, left.y-right.y);
}
//End of Operator overloads