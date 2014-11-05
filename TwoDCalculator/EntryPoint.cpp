#include "RenderUI.h"
#include "Engine.h"
#include <Vector2D.h>
#include <iostream>
#include <Matrix2D.h>
#include <Matrix3D.h>
#include <Vector3D.h>

//Vectors Start
Vector2D left;
Vector2D right;
Vector2D result;

Vector2D originalVector;
Vector2D normalVector;
Vector2D cwPerpendicularVector;
Vector2D ccwPerpendicularVector;

Vector2D vector1;
Vector2D vector2;
Vector2D projectionVector;
Vector2D rejectionVector;

Vector2D aVector;
Vector2D bVector;
Vector2D aMinusBVector;
Vector2D aVectorLerpPort;
Vector2D bVectorLerpPort;
Vector2D lerpResVector;

Vector2D resultM;

Vector3D affineResults[5];
int numResults=5;

float dogHouse=.3;
int maxMatrixIndex = 0;
Vector2D bLeft(-dogHouse,-dogHouse);
Vector2D tLeft(-dogHouse, dogHouse);
Vector2D tRight(dogHouse, dogHouse);
Vector2D bRight(dogHouse, -dogHouse);
Vector2D tRoof(0,dogHouse+dogHouse);
Vector2D dogLines[]=
{
	bLeft, tLeft,
	tLeft, tRight,
	tRight, bRight,
	bRight, bLeft,
	tLeft, tRoof,
	tRight, tRoof
};
int numLines=(sizeof(dogLines)/sizeof(*dogLines))/2;
Matrix3D transMatrix[10];
Matrix3D curTranMatrix;
//Vectors End


//Start of Callbacks
void MyBasicVectorEquationCallback(const BasicVectorEquationInfo& info)
{
	left=info.scalar1*Vector2D(info.x1,info.y1);
	right=info.scalar2*Vector2D(info.x2,info.y2);

	if(info.add)
	{
		result=left+right;
	}
	else
	{
		result=left-right;
	}
};

void MyPerpendicularDataCallback(const PerpendicularData& info)
{
	originalVector=Vector2D(info.x,info.y);

	if(originalVector.x!=0 && originalVector.y!=0)
		normalVector=normalize(originalVector);

	cwPerpendicularVector=perpCW(originalVector);
	ccwPerpendicularVector=perpCCW(originalVector);
};

void MyDotProductDataCallback(const DotProductData& info)
{
	vector1=Vector2D(info.v1i,info.v1j);
	vector2=Vector2D(info.v2i,info.v2j);
	
	if(info.projectOntoLeftVector)
	{
		projectionVector=(Dot(vector1, vector2)/Length(vector1))*normalize(vector1);
		rejectionVector=vector2-projectionVector;
	}
	else
	{
		projectionVector=(Dot(vector1, vector2)/Length(vector2))*normalize(vector2);
		rejectionVector=vector1-projectionVector;
	}
};

void MyLerpDataCallback(const LerpData& info)
{
	aVector=Vector2D(info.a_i,info.a_j);
	bVector=Vector2D(info.b_j,info.b_j);

	aMinusBVector=bVector-aVector;

	aVectorLerpPort=((1-info.beta)*aVector);
	bVectorLerpPort=(info.beta*bVector);

	lerpResVector=Lerp(aVector, bVector, info.beta);
};

void MyLinearTransformationCallback(const LinearTransformationData& data)
{
	resultM=Vector2D(data.v0,data.v1);
	Matrix2D op=Matrix2D(Vector2D(data.m00,data.m01),Vector2D(data.m10,data.m11));
	resultM=(op*resultM);
};

void MyAffineTransformationCallback(const AffineTransformationData& data)
{
	Matrix3D m1;
	m1.m00=data.data[0]; m1.m01=data.data[1]; m1.m02=data.data[2];
	m1.m10=data.data[3]; m1.m11=data.data[4]; m1.m12=data.data[5];
	m1.m20=data.data[6]; m1.m21=data.data[7]; m1.m22=data.data[8];

	for(int i=0; i<numResults; i++)
	{
		affineResults[i].x=data.data[(i*3+9)];
		affineResults[i].y=data.data[(i*3+10)];
		affineResults[i].z=data.data[(i*3+11)];
	}

	for(int i=0; i<numResults; i++)
	{
		affineResults[i]=(m1*affineResults[i]);
	}
};

void MyMatrixTransform2DCallback(const MatrixTransformData2D& data)
{
	Matrix3D indexMatrix;
	curTranMatrix=indexMatrix;
	Matrix3D tempMatrix;
	Matrix3D scaleMatrix=curTranMatrix.ScaleX(data.scaleX)*curTranMatrix.ScaleY(data.scaleY);
	Matrix3D rotationMatrix=curTranMatrix.Rotation(data.rotate);
	Matrix3D translateMatrix=curTranMatrix.Translation(data.translateX,data.translateY);

	if(data.selectedMatrix>maxMatrixIndex)
		maxMatrixIndex=data.selectedMatrix;

	transMatrix[data.selectedMatrix]=scaleMatrix*rotationMatrix*translateMatrix;

	for(int i=0; i<=maxMatrixIndex;i++)
	{
		curTranMatrix=curTranMatrix*transMatrix[i];
	}
};
//End of Callbacks

int main(int argc, char* argv[])
{
	Engine::Init();

	RenderUI renderUI;

	renderUI.setBasicVectorEquationData(MyBasicVectorEquationCallback, left, right, result);

	renderUI.setPerpendicularData(originalVector,normalVector,cwPerpendicularVector,ccwPerpendicularVector,MyPerpendicularDataCallback);

	renderUI.setDotProductData(vector1, vector2, projectionVector, rejectionVector, MyDotProductDataCallback);

	renderUI.setLerpData(aVector, bVector, aMinusBVector, aVectorLerpPort, bVectorLerpPort, lerpResVector, MyLerpDataCallback);

	renderUI.setLinearTransformationData(resultM, MyLinearTransformationCallback);

	renderUI.setAffineTransformationData(affineResults[0],MyAffineTransformationCallback);

	renderUI.set2DMatrixVerticesTransformData(dogLines[0], numLines, transMatrix[0],curTranMatrix,MyMatrixTransform2DCallback);

	if( ! renderUI.initialize(argc, argv))
		return -1;
	return renderUI.run();
}


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
	return Vector2D(scalar*right.x, scalar*right.y);
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

Matrix2D operator*(const Matrix2D& m1, const Matrix2D& m2)
{
	return Matrix2D(Vector2D((m1.m00*m2.m00+m1.m01*m2.m10),(m1.m00*m2.m01+m1.m01*m2.m11)),Vector2D((m1.m10*m2.m00+m1.m11*m2.m10),(m1.m10*m2.m01+m1.m11*m2.m11)));
}

Vector2D operator*(const Matrix2D& m1, const Vector2D v1)
{
	return Vector2D((m1.m00*v1.x)+(m1.m10*v1.y),(m1.m01*v1.x)+(m1.m11*v1.y));
}

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
//End of Operator overloads