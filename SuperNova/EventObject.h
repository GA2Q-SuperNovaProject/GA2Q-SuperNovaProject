#pragma once
#include <vector>
#include <stack>
#include "GameObject.h"

class Scene;
class Player;
class GameUI;

class EventObject : public GameObject
{
public:
	EventObject(eObjectTag tag, eObjectName name, Transform transform);
	~EventObject();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	//void SetTimer(1,FRAME_RATE,)

private:
	Vec2 m_beginPos;
	Vec2 m_IceTemp;
	Vec2 m_mousePos;

	float TestTime = 10.f;

	bool alreadyStarted = true;

	bool m_isMusicStart;
	bool m_isMusicStarted;
	
	bool m_starDraw = false;
	bool m_DrawGIF = false;
	bool m_EventStart = true;
	bool m_StarCount = true;

	bool m_BearTouch = false;
	bool m_DeerTouch = false;
	bool m_EagleTouch = false;
	bool m_WhaleTouch = false;
	bool m_GrandpaTouch = false;

	//true가 될 시 gif이벤트 발생
	bool m_BearEvent = false;
	bool m_DeerEvent = false;
	bool m_EagleEvent = false;
	bool m_WhaleEvent = false;
	bool m_GrandpaEvent = false;

	int m_starImage;
	int m_star1Count = 0;
	int m_star2Count = 0;
	int m_star3Count = 0;

	std::vector<Vec2> m_star1List;
	std::vector<Vec2> m_star2List;
	std::vector<Vec2> m_star3List;

	GameObject* m_pPlayer;
	GameUI* m_StarPiece1;
	GameUI* m_StarPiece2;
	GameUI* m_StarPiece3;
	BoxCollider* m_boxCol;

	void Sortation();
	void PortalEvent();
	void StoryPrint();
	void StatueEvent();
	void DragStars();
	void StarEffectSound(int starImage);
};

