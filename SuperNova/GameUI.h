#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "SoundManager.h"
#include "StructDefine.h"

class Player;
class OptionUI;

class GameUI : public GameObject
{
public:
	GameUI(eObjectTag tag, eObjectName name, Transform transform);
	~GameUI();

	virtual void Start();
	virtual void Update() override;
	virtual void Render() override;

	bool GetStartPiece(eObjectName star);

	//int m_StarPiece1count1 = 0;
	//int m_StarPiece1count2 = 0;
	//int m_StarPiece1count3 = 0;

private:
	Vec2 m_beginPos;	// 처음 시작할때 오브젝트 위치를 받아오는 변수
	bool m_isClick;

	bool m_ShowNoteMain = false;

	bool m_DragOn;
	bool m_Star1;
	bool m_Star2;
	bool m_Star3;

	bool m_OptionClick;

	int m_boostCount;

	Vec2 m_mousePos;

	void Sortation();
	void ClickEvent();

	void BoostCheck();
	void VolumeEvent();

	void CheckHpCount();
	void DrawStarPieceCount();
	void ShowNoteMain();
	static int m_hpCheck;

	static bool IsGameOptionOn;
	
	Player* playerObject;
	OptionUI* optionObject;

	Rect2D optionRect =
	{
		610,
		190,
		1310,
		890
	};
};


