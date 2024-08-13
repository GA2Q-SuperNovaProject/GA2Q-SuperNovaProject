#include "Shape.h"
#include <iostream>

/// <summary>
/// ������ �޸� ������ �ٸ��� �ؾ� �� ����!
/// </summary>
/// <param name="radius"></param>

CircleShape::CircleShape(const float radius)
{
	this->radius = radius;
	//std::cout << "CircleShape Construct" << std::endl;
}

CircleShape::~CircleShape()
{
	//std::cout << "CircleShape Destruct" << std::endl;
}

ShapeType CircleShape::GetType() const
{
	return CIRCLE;
}

Shape* CircleShape::Clone() const
{
	return new CircleShape(this->radius);
}

float CircleShape::GetMomentOfInertia() const
{
	return 0.5f * (radius * radius); //������ �������� ������� �Ѵ�!
}

PolygonShape::PolygonShape(const std::vector<Vec2> vertices)
{
	//std::cout << "PolygonShape Construct" << std::endl;
}

PolygonShape::~PolygonShape()
{
	//std::cout << "PolygonShape Destruct" << std::endl;
}

ShapeType PolygonShape::GetType() const
{
	return POLYGON;
}

Shape* PolygonShape::Clone() const
{
	return new PolygonShape(this->localVertices); 
	//Q: �ٵ� ��? �׳� �������ϸ� �ɰ����� �̷��� �� ��
}

float PolygonShape::GetMomentOfInertia() const
{
	return 0.0f; ///�߰� ����.
}

void PolygonShape::UpdateVertices(float angle, const Vec2& position)
{
	//Local���� World Space��, Vertice���� ���� ���� ��. 
	for (int i = 0; i < localVertices.size(); i++)
	{
		//�켱 ȸ��, Translate.  
		///9:36 
	}
}

BoxShape::BoxShape(float width, float height)
{ 
	//std::cout << "BoxShape Construct" << std::endl;
	//PolygonShape�� ��ӹ޴� ���� -> �ٸ�, PolygonShape�� �⺻ �����ڰ�
	//�ڵ����� ȣ��ȴ�! default. 
	this->width = width;
	this->height = height;
	//�ڽ� ���� ������ ȣ��

	localVertices.push_back(Vec2(-width / 2.0, -height / 2.0)); //�ð����
	localVertices.push_back(Vec2(width / 2.0, -height / 2.0));
	localVertices.push_back(Vec2(width / 2.0, height / 2.0));
	localVertices.push_back(Vec2(-width / 2.0, height / 2.0));
}

BoxShape::~BoxShape()
{
	//std::cout << "BoxShape Destruct" << std::endl;
}

ShapeType BoxShape::GetType() const
{
	return BOX; //�������� ENUM ����.
}

Shape* BoxShape::Clone() const
{
	return new BoxShape(width, height);
}

float BoxShape::GetMomentOfInertia() const
{
	return (0.083333) * (width * width + height * height); //����, ������ Mass ���� ���ؾ�!
}
