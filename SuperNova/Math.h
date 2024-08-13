#pragma once
#include "Vec2.h"
class Transform;
struct Vec2Rect;

namespace Math
{
	double Deg2Rad(double deg);
	float GetAngleDeg(Vec2 v1, Vec2 v2);
	float Epsilon();
	Vec2 ApplyTransform(const Vec2& vector, const Transform& transform);

	//두 벡터 사이 각도 리턴 -> Radian으로 리턴!
	double AngleBetweenVectorsRad(const Vec2& a, const Vec2& b);

	///[TW] OBB용으로 쓰이는 애들.
	double AbsDotVector(Vec2 a, Vec2 b); //절댓값 + 내적.
	Vec2 DistanceVector(const Vec2Rect& a, const Vec2Rect& b); //거리 측정 벡터.
	Vec2 GetHeightVector(const Vec2Rect& a, float itsRotation); //높이 벡터
	Vec2 GetWidthVector(const Vec2Rect& a, float itsRotation); //너비 벡터.

	///[TW] => Circle-Rectangle을 위해!
	bool PointInOBBRectangle(const Vec2Rect& rect, Vec2 point);
	double DistancePointToLine(Vec2 lineEndA, Vec2 lineEndB, Vec2 point);
	double DistancePointToLineSegment(Vec2 lineEndA, Vec2 lineEndB, Vec2 point);

	double DistanceTwoVectors(Vec2 a, Vec2 b);
	double DistanceTwoVectorsPow(Vec2 a, Vec2 b);


};