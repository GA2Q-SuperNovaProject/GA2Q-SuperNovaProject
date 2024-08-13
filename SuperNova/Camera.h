#pragma once
#include "Vec2.h"
#include "StructDefine.h"
class GameObject;

/// <summary>
/// GameObject�� ���󰡴� Camera
/// 2023.02.07 [MinseoChoi]
/// </summary>
class Camera
{
public:
	static Camera& GeInstance()
	{
		static Camera ins;
		return ins;
	}

	void Initialize();
	void Update();

	void PlayerInit();	// ī�޶��� �߽��� �Ǵ� GameObject��ü(Player) Init
	void FollowPlayer(Vec2 moveAt, GameObject* playerObj);			// �÷��̾��� �����ӿ� ���� ���� �����̴� ī�޶�
	//Rect2D PlayerMoveSection();			// ī�޶��� ������ ���� �÷��̾ �����̴� ����

	Vec2 WorldToCameraPOINT(Vec2 worldPoint);		// ���� ��ǥ�� ī�޶� ��ǥ�� �ٲپ��ִ� �Լ�
	Vec2 WorldToCameraPOINT_UI(Vec2 worldPoint);	// ���� ��ǥ�� ī�޶� ��ǥ�� �ٲپ��ִ� �Լ�(UI ����)
	Vec2 CameraToWorldPOINT(Vec2 cameraPoint);		// ī�޶� ��ǥ�� ���� ��ǥ�� �ٲپ��ִ� �Լ�
	Vec2 RelativeSpawnPOINT(Vec2 spawnPOINT);		// �÷��̾��� ��ġ�� ���� ������Ʈ�� ����? ����
	void Vec2RectToCameraPOINT(Vec2Rect& worldRect); //Vec2Rect�� ��ȯ���ִ� �Լ�. (������ �Ű�����)
	void Vec2CircleToCameraPOINT(Vec2Circle& worldCircle); //Vec2Circle�� ��ȯ���ִ� �Լ�. (������ �Ű�����)
	Rect2D GetCameraRect() const;								// ī�޶��� ������ ��ȯ�ϴ� �Լ�
	Vec2 GetCameraCenterPos() const { return m_centerPos; }		// ī�޶��� ������ ��ȯ�ϴ� �Լ�
	Vec2 GetCameraLeftTopPos() const { return m_leftTopPos; }	// ī�޶��� ����������� ��ȯ�ϴ� �Լ�

private:
	Camera();
	~Camera();	

	const float m_moveSectionX = 1200.f;	// ī�޶� ������ ���� ����(X��)���� �÷��̾ �����̴� ����
	const float m_moveSectiony = 685.f;		// ī�޶� ������ ���� ����(Y��)���� �÷��̾ �����̴� ����

	float m_width;
	float m_height;
	
	Vec2 m_beginLeftTopPos;
	Vec2 m_leftTopPos;
	Vec2 m_centerPos;

	GameObject* m_pPlayer;	
};

 