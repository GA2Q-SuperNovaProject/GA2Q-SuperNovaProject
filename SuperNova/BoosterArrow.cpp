#include "BoosterArrow.h"
#include "Debug.h"
#include "Camera.h"
#include "InputManager.h"
#include "Vec2.h"
#include "RenderSystem.h"
#include "Transform.h"

using namespace std;

BoosterArrow::BoosterArrow(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), temp(transform.GetPosition())

{

}

BoosterArrow::~BoosterArrow()
{

}
//const int VK_LMB = 0x01; //좌클릭
//const int VK_RMB = 0x02; //우클릭

void BoosterArrow::Update()
{
	//메테오가 플레이어 위치 체크하면서 따라가야함
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT_UI(temp));
}

void BoosterArrow::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());

}

