#pragma once
#include "Vec2.h" //구현의 편의를 위해 Vec2 좌표를 반환하는 멤버 함수 작성 [TW]
/// <summary>
/// 공용으로 쓰일 struct
/// 2023.02.07 [MinseoChoi]
/// </summary>

// 콜라이더 도입을 위해 Vec2 좌표 네개로 구성된 Struct, (BoxCollider) [TW]
struct Vec2Rect
{
	Vec2Rect() {}
	Vec2Rect(Vec2 tL, Vec2 tR, Vec2 bL, Vec2 bR) :
		topLeft(tL), topRight(tR), bottomLeft(bL), bottomRight(bR)
	{}

	Vec2 topLeft;
	Vec2 topRight;
	Vec2 bottomLeft;
	Vec2 bottomRight;
};

// 콜라이더 도입을 위해 중심좌표와 Radius로 구성된 Struct, (CircleCollider) [TW]
struct Vec2Circle
{
	Vec2 position;
	float radius;
};

struct Rect2D
{
	float left;
	float top;
	float right;
	float bottom;

	Vec2 GetTL() //Top-Left 좌상단 벡터 반환
	{
		return Vec2(left, top);
	}

	Vec2 GetTR() //Top-Right 우상단 벡터 반환
	{
		return Vec2(right, top);
	}

	Vec2 GetBL() //Bottom-Left 좌하단 벡터 반환
	{
		return Vec2(left, bottom);
	}

	Vec2 GetBR() //Bottom-Right 우하단 벡터 반환
	{
		return Vec2(right, bottom);
	}

	Vec2Rect ToVec2Rect()
	{
		return Vec2Rect(GetTL(), GetTR(), GetBL(), GetBR());
	}

	void SetTL(Vec2 vec)
	{
		left = vec.x;
		top = vec.y;
	}

	void SetBR(Vec2 vec)
	{
		right = vec.x;
		bottom = vec.y;
	}
};

struct AreaCount //행렬 계산에 따로 쓰는 자료형이다. 
{
	float area[3];
};

