#include "BoosterGage.h"
#include "Debug.h"
#include "Camera.h"
#include "InputManager.h"
#include "Vec2.h"
#include "RenderSystem.h"
#include "Transform.h"


using namespace std;

BoosterGage::BoosterGage(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), temp(transform.GetPosition()),
	m_boostcount(3)

{

}

BoosterGage::~BoosterGage()
{

}
//const int VK_LMB = 0x01; //좌클릭
//const int VK_RMB = 0x02; //우클릭

void BoosterGage::Update()
{
	//메테오가 플레이어 위치 체크하면서 따라가야함
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT_UI(temp));
	if (InputManager::GetInstance().IsKeyDown(VK_Space))
	{
		m_boostcount--;
		m_imageIndex--;
		if (m_boostcount <= 0 && InputManager::GetInstance().IsKeyDown(VK_Space))
		{
			m_boostcount = 0;
			m_imageIndex = IMAGE_BOOSTER_GAGE0;
		}
	}
	//0밑으로 내려가지 않는 것 확인
	
	if (InputManager::GetInstance().IsKeyDown(VK_Q))
	{
		m_boostcount++;
		m_imageIndex++;
		if (m_boostcount >= 3 && InputManager::GetInstance().IsKeyDown(VK_Q))
		{
			m_boostcount = 3;
			m_imageIndex = IMAGE_BOOSTER_GAGE3;
		}
	}
}

void BoosterGage::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());

}

