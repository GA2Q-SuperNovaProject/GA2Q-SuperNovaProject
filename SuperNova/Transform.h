#pragma once
#include "Vec2.h"
class Transform
{
public:
	Transform(Vec2 position, float rotation, Vec2 scale); //Collider�� �ڵ������� �����ȴ�.
	virtual ~Transform();

	Vec2 GetPosition() const { return m_Position; }
	void SetPosition(Vec2 val) { m_Position = val; }

	//[TW] �ڵ����� 360���� ������ ����.
	float GetRotation() const;
	void SetRotation(float val) { m_Rotation = val; }

	Vec2 GetScale() const { return m_Scale; }
	void SetScale(Vec2 val) { m_Scale = val; }

	/// Get-Setter�� �����鼭 �� Value�� Public���� ����?
	/// -> L-Value, R-Value ���� ��� ���� [TW]
	Vec2 m_Position;
	float m_Rotation;
	Vec2 m_Scale; //[TW] �����ϸ� Circle�� ��ü ����, Scale�� x,y�� ���� �� ��. Rect�� ���X.

private:
	
};

/// [TW] �������� �ٲ� ü��:
/// Transform�� m_position�� ���� ���̰�, 
/// GameObject���� m_Position�� ���� ���� ��ġ�� Transform���� ��ü�� ��.
/// GameObject�� ���������� �����ڿ��� �����Ҵ�� Transform�� ���� ������, (������)
///  ���������� �ڽ��� �����ڿ��� ���� �Ҵ�� Collider�� ���� �ִ�.
/// �翬��, GameObject�� � ������� ���� �ʿ䵵 �ְ� (eColType ����).

/// �̸� �ڿ������� ������ ü������ �ϼ� ��,
/// �� ���� ���� ã��/Instantiate �� ��.
/// 
/// ���߿� Transform ���ַ� Position�� �ٲپ��!

///����� D2D SetTransform Ȱ��, �浹ó�� ���ؼ� �̴� �Ŀ� �ٲ�.
///
