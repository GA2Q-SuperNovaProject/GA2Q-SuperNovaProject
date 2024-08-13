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

	//�� ���� ���� ���� ���� -> Radian���� ����!
	double AngleBetweenVectorsRad(const Vec2& a, const Vec2& b);

	///[TW] OBB������ ���̴� �ֵ�.
	double AbsDotVector(Vec2 a, Vec2 b); //���� + ����.
	Vec2 DistanceVector(const Vec2Rect& a, const Vec2Rect& b); //�Ÿ� ���� ����.
	Vec2 GetHeightVector(const Vec2Rect& a, float itsRotation); //���� ����
	Vec2 GetWidthVector(const Vec2Rect& a, float itsRotation); //�ʺ� ����.

	///[TW] => Circle-Rectangle�� ����!
	bool PointInOBBRectangle(const Vec2Rect& rect, Vec2 point);
	double DistancePointToLine(Vec2 lineEndA, Vec2 lineEndB, Vec2 point);
	double DistancePointToLineSegment(Vec2 lineEndA, Vec2 lineEndB, Vec2 point);

	double DistanceTwoVectors(Vec2 a, Vec2 b);
	double DistanceTwoVectorsPow(Vec2 a, Vec2 b);


};