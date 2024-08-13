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
//const int VK_LMB = 0x01; //��Ŭ��
//const int VK_RMB = 0x02; //��Ŭ��

void BoosterArrow::Update()
{
	//���׿��� �÷��̾� ��ġ üũ�ϸ鼭 ���󰡾���
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT_UI(temp));
}

void BoosterArrow::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());

}

