#include "Math.h"
#include <cmath>
#include "Vec2.h"
#include <limits>
#include "Transform.h"
#include "StructDefine.h"
#include "Matrix2D.h"


double Math::Deg2Rad(double deg)
{
	return deg / 180 * 3.141592;
}

float Math::GetAngleDeg(Vec2 v1, Vec2 v2)
{
	return acos(v1.Dot(v2) / v1.Magnitude() * v2.Magnitude());
}

float Math::Epsilon()
{
	return std::numeric_limits<float>::epsilon();
}

Vec2 Math::ApplyTransform(const Vec2& vector, const Transform& transform)
{
	//실제 행렬계산을 반영한 값을 반환할 예정.
	float scaleList[9] = { transform.GetScale().x,0,0,
							0,transform.GetScale().y,0,
							0,0,1 };
	Matrix2D scaleMatrix(scaleList);

	double rotRad = Math::Deg2Rad(transform.GetRotation());
	float rotList[9] = { cos(rotRad),-sin(rotRad),0,
						sin(rotRad),cos(rotRad),0,
						0,0,1 };
	Matrix2D rotMatrix(rotList);
	rotMatrix = rotMatrix.Transpose(); //이로써 Rotation까지는 Fix.

	Matrix2D midMatrix = scaleMatrix * rotMatrix; //오버로딩을 통해 곱.

	//이 경우, TRST' 중에서 SR순서대로 간 것. 그러니, T' SR T 순서대로 곱하자.

	//완성된 Transform Matrix * 현 위치, (3x1 벡터행렬)이 적용되는 것. 
	//이 경우, Pivot Point를 행렬에다가 적는 것이다.

	//T'
	float decreList[9] = { 1, 0, -(transform.GetPosition().x),
						  0, 1, -(transform.GetPosition().y),
						  0, 0, 1 };
	Matrix2D decrement(decreList);
	decrement = decrement.Transpose();

	//T
	float increList[9] = { 1, 0, (transform.GetPosition().x),
						   0, 1, (transform.GetPosition().y),
						   0, 0, 1 };
	Matrix2D increment(increList);
	increment = increment.Transpose();

	Matrix2D transMatrix = decrement * midMatrix * increment;
	//이제야 T'RST 완성.

	AreaCount tmp;
	tmp.area[0] = vector.x;
	tmp.area[1] = vector.y;
	tmp.area[2] = 1;

	tmp = transMatrix * tmp;

	Vec2 toReturn = { tmp.area[0],tmp.area[1] };
	return toReturn;
}

double Math::AngleBetweenVectorsRad(const Vec2& a, const Vec2& b)
{
	double dotProduct = a.Dot(b);
	double magProduct = a.Magnitude() * b.Magnitude();
	double angleRadian = acos(dotProduct / magProduct);
	return angleRadian;
}

double Math::AbsDotVector(Vec2 a, Vec2 b)
{
	return fabs(a.x * b.x + a.y * b.y); //내적 벡터의 절댓값.
}


Vec2 Math::DistanceVector(const Vec2Rect& a, const Vec2Rect& b)
{
	Vec2 ret;
	float tmpWidthA = fabs(a.topRight.x - a.topLeft.x);
	float tmpHeightA = fabs(a.topRight.y - a.bottomRight.y);

	float tmpWidthB = fabs(b.topRight.x - b.topLeft.x);
	float tmpHeightB = fabs(b.topRight.y - b.bottomRight.y);

	ret.x = (a.topLeft.x + tmpWidthA / 2.0f) - (b.topLeft.x + tmpWidthB / 2.0f);
	ret.y = (a.topLeft.y + tmpHeightA / 2.0f) - (b.topLeft.y + tmpHeightB / 2.0f);
	return ret;
}

Vec2 Math::GetHeightVector(const Vec2Rect& a, float itsRotation) //높이 벡터
{
	Vec2 ret;
	float tmpHeightA = fabs(a.topRight.y - a.bottomRight.y);

	ret.x = tmpHeightA * cos(Math::Deg2Rad(itsRotation - 90)) / 2.0f;
	ret.y = tmpHeightA * sin(Math::Deg2Rad(itsRotation - 90)) / 2.0f;
	return ret;
}

Vec2 Math::GetWidthVector(const Vec2Rect& a, float itsRotation) //너비 벡터.
{
	Vec2 ret;
	float tmpWidthA = fabs(a.topRight.x - a.topLeft.x);

	ret.x = tmpWidthA * cos(Math::Deg2Rad(itsRotation)) / 2.0f;
	ret.y = tmpWidthA * sin(Math::Deg2Rad(itsRotation)) / 2.0f;
	return ret;
}

// OBB 직사각형...
bool Math::PointInOBBRectangle(const Vec2Rect& rect, Vec2 point)
{
	float amab = (rect.topLeft - point).Dot(rect.topLeft - rect.topRight);
	float abab = (rect.topLeft - rect.topRight).Dot(rect.topLeft - rect.topRight);
	float amad = (rect.topLeft - point).Dot(rect.topLeft - rect.bottomLeft);
	float adad = (rect.topLeft - rect.bottomLeft).Dot(rect.topLeft - rect.bottomLeft);

	return ((0 < amab && amab < abab) && (0 < amad && amad < adad));
}

double Math::DistancePointToLine(Vec2 lineEndA, Vec2 lineEndB, Vec2 point)
{
	double normalLength = _hypot(lineEndB.x - lineEndA.x, lineEndB.y - lineEndA.y);
	double distance = (double)((point.x - lineEndA.x) * (lineEndB.y - lineEndA.y) - (point.y - lineEndA.y) * (lineEndB.x - lineEndA.x)) / normalLength;
	distance = fabs(distance);
	return distance;
}

double Math::DistancePointToLineSegment(Vec2 lineEndA, Vec2 lineEndB, Vec2 goalPoint)
{
	// vector AB
	Vec2 tempAB;
	tempAB.x = lineEndB.x - lineEndA.x;
	tempAB.y = lineEndB.y - lineEndA.y;

	// vector BP
	Vec2 tempBE;
	tempBE.x = goalPoint.x - lineEndB.x;
	tempBE.y = goalPoint.y - lineEndB.y;

	// vector AP
	Vec2 tempAE;
	tempAE.x = goalPoint.x - lineEndA.x;
	tempAE.y = goalPoint.y - lineEndA.y;

	// Variables to store dot product
	double dotOne, dotTwo;

	// Calculating the dot product
	dotOne = (tempAB.x * tempBE.x + tempAB.y * tempBE.y);
	dotTwo = (tempAB.x * tempAE.x + tempAB.y * tempAE.y);

	double reqAns = 0;

	// Case 1
	if (dotOne > 0) {

		// Finding the magnitude
		double y = goalPoint.y - lineEndB.y;
		double x = goalPoint.x - lineEndB.x;
		reqAns = sqrt(x * x + y * y);
	}

	// Case 2
	else if (dotTwo < 0) {
		double y = goalPoint.y - lineEndA.y;
		double x = goalPoint.x - lineEndA.x;
		reqAns = sqrt(x * x + y * y);
	}
	// Case 3
	else {

		// Finding the perpendicular distance
		double x1 = tempAB.x;
		double y1 = tempAB.y;
		double x2 = tempAE.x;
		double y2 = tempAE.y;
		double mod = sqrt(x1 * x1 + y1 * y1);
		reqAns = fabs(x1 * y2 - y1 * x2) / mod;
	}
	return reqAns;
}

double Math::DistanceTwoVectors(Vec2 a, Vec2 b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double Math::DistanceTwoVectorsPow(Vec2 a, Vec2 b)
{
	return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}




