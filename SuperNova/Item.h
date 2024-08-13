#pragma once
#include "GameObject.h"

class Player;
class GameUI;

class Item : public GameObject
{
public:
	Item(eObjectTag tag, eObjectName name, Transform transform);
	~Item();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;


private:
	bool m_isMusicStart;

	Vec2 m_beginPos;
	void Sortation();

	GameObject* m_pPlayer;
	Player* m_pRealPlayer;
	GameUI* m_pGameUI;

	bool m_isChecked = false;

	void ItemEvent();
	void EffectSound();
};
