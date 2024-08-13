#pragma once
#include "Vec2.h"
#include "StructDefine.h"
class GameObject;

/// <summary>
/// GameObject를 따라가는 Camera
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

	void PlayerInit();	// 카메라의 중심이 되는 GameObject객체(Player) Init
	void FollowPlayer(Vec2 moveAt, GameObject* playerObj);			// 플레이어의 움직임에 따라 같이 움직이는 카메라
	//Rect2D PlayerMoveSection();			// 카메라의 움직임 없이 플레이어만 움직이는 영역

	Vec2 WorldToCameraPOINT(Vec2 worldPoint);		// 월드 좌표를 카메라 좌표로 바꾸어주는 함수
	Vec2 WorldToCameraPOINT_UI(Vec2 worldPoint);	// 월드 좌표를 카메라 좌표로 바꾸어주는 함수(UI 전용)
	Vec2 CameraToWorldPOINT(Vec2 cameraPoint);		// 카메라 좌표를 월드 좌표로 바꾸어주는 함수
	Vec2 RelativeSpawnPOINT(Vec2 spawnPOINT);		// 플레이어의 위치에 따라 오브젝트를 생성? 해줌
	void Vec2RectToCameraPOINT(Vec2Rect& worldRect); //Vec2Rect를 변환해주는 함수. (참조자 매개변수)
	void Vec2CircleToCameraPOINT(Vec2Circle& worldCircle); //Vec2Circle를 변환해주는 함수. (참조자 매개변수)
	Rect2D GetCameraRect() const;								// 카메라의 중점을 반환하는 함수
	Vec2 GetCameraCenterPos() const { return m_centerPos; }		// 카메라의 중점을 반환하는 함수
	Vec2 GetCameraLeftTopPos() const { return m_leftTopPos; }	// 카메라의 좌측상단점을 반환하는 함수

private:
	Camera();
	~Camera();	

	const float m_moveSectionX = 1200.f;	// 카메라 움직임 없이 가로(X축)에서 플레이어가 움직이는 공간
	const float m_moveSectiony = 685.f;		// 카메라 움직임 없이 세로(Y축)에서 플레이어가 움직이는 공간

	float m_width;
	float m_height;
	
	Vec2 m_beginLeftTopPos;
	Vec2 m_leftTopPos;
	Vec2 m_centerPos;

	GameObject* m_pPlayer;	
};

 