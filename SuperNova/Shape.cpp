#include "Shape.h"
#include <iostream>

/// <summary>
/// 옵젝별 메모리 관리는 다르게 해야 할 문제!
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
	return 0.5f * (radius * radius); //여전히 질량과도 곱해줘야 한다!
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
	//Q: 근데 왜? 그냥 값복사하면 될것이지 이렇게 왜 함
}

float PolygonShape::GetMomentOfInertia() const
{
	return 0.0f; ///추가 요함.
}

void PolygonShape::UpdateVertices(float angle, const Vec2& position)
{
	//Local에서 World Space로, Vertice들을 루프 돌릴 것. 
	for (int i = 0; i < localVertices.size(); i++)
	{
		//우선 회전, Translate.  
		///9:36 
	}
}

BoxShape::BoxShape(float width, float height)
{ 
	//std::cout << "BoxShape Construct" << std::endl;
	//PolygonShape를 상속받는 구조 -> 다만, PolygonShape의 기본 생성자가
	//자동으로 호출된다! default. 
	this->width = width;
	this->height = height;
	//박스 내부 폴리곤 호출

	localVertices.push_back(Vec2(-width / 2.0, -height / 2.0)); //시계방향
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
	return BOX; //개별적인 ENUM 설정.
}

Shape* BoxShape::Clone() const
{
	return new BoxShape(width, height);
}

float BoxShape::GetMomentOfInertia() const
{
	return (0.083333) * (width * width + height * height); //물론, 여전히 Mass 따로 곱해야!
}
