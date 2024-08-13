#pragma once
#include <vector>
#include "Vec2.h"

enum ShapeType
{
	CIRCLE,
	POLYGON,
	BOX //BOX�� Polygon�� �Ϻη� ��޵� ��������, �ϴ� ���� ����.
};

class Shape
{
public:
	virtual ~Shape() = default; //���� �Ҹ��� �⺻.
	virtual ShapeType GetType() const abstract; //Ÿ���� ����, ��ӹ��� ���̴�. 
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
	std::vector<Vec2> localVertices; //���� �������� �켱������ ���, 
	//��Ľ��� ���ؼ� -> ���� �������� ��ȯ.
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

