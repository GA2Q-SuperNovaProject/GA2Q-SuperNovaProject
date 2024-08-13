#pragma once
#include <vector>
#include "Vec2.h"

enum ShapeType
{
	CIRCLE,
	POLYGON,
	BOX //BOX도 Polygon의 일부로 취급될 것이지만, 일단 따로 구분.
};

class Shape
{
public:
	virtual ~Shape() = default; //가상 소멸자 기본.
	virtual ShapeType GetType() const abstract; //타입을 리턴, 상속받을 것이다. 
	virtual Shape* Clone() const abstract;
	virtual float GetMomentOfInertia() const abstract;
};

class CircleShape : public Shape
{
public:
	float radius;
	CircleShape(const float radius);
	virtual ~CircleShape();
	ShapeType GetType() const override;
	virtual Shape* Clone() const override;
	float GetMomentOfInertia() const override;
};

class PolygonShape : public Shape
{
public:
	std::vector<Vec2> localVertices; //로컬 선분으로 우선적으로 계산, 
	//행렬식을 통해서 -> 월드 선분으로 변환.
	std::vector<Vec2> worldVertices; 

	PolygonShape() = default;
	PolygonShape(const std::vector<Vec2> vertices);
	virtual ~PolygonShape();

	ShapeType GetType() const override;
	virtual Shape* Clone() const override;
	float GetMomentOfInertia() const override;
	void UpdateVertices(float angle, const Vec2& position);
};

class BoxShape : public PolygonShape
{
public:
	float width;
	float height;
	BoxShape(float width, float height);
	virtual ~BoxShape();
	ShapeType GetType() const override;
	virtual Shape* Clone() const override;
	float GetMomentOfInertia() const override;
};

