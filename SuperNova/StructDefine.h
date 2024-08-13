#pragma once
#include "Vec2.h" //������ ���Ǹ� ���� Vec2 ��ǥ�� ��ȯ�ϴ� ��� �Լ� �ۼ� [TW]
/// <summary>
/// �������� ���� struct
/// 2023.02.07 [MinseoChoi]
/// </summary>

// �ݶ��̴� ������ ���� Vec2 ��ǥ �װ��� ������ Struct, (BoxCollider) [TW]
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

// �ݶ��̴� ������ ���� �߽���ǥ�� Radius�� ������ Struct, (CircleCollider) [TW]
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

	Vec2 GetTL() //Top-Left �»�� ���� ��ȯ
	{
		return Vec2(left, top);
	}

	Vec2 GetTR() //Top-Right ���� ���� ��ȯ
	{
		return Vec2(right, top);
	}

	Vec2 GetBL() //Bottom-Left ���ϴ� ���� ��ȯ
	{
		return Vec2(left, bottom);
	}

	Vec2 GetBR() //Bottom-Right ���ϴ� ���� ��ȯ
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

struct AreaCount //��� ��꿡 ���� ���� �ڷ����̴�. 
{
	float area[3];
};

