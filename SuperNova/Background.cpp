#include "Background.h"
#include "RenderSystem.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"
#include "Debug.h"

using namespace std;

Background::Background(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), m_beginPos(transform.GetPosition()), m_moving(false)
{
	Sortation();
}

Background::~Background()
{

}

void Background::Update()
{
	if (m_moving) // m_moving == true
	{
		m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(m_beginPos));
	}
}

void Background::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
}

void Background::Sortation()
{
	switch (m_name)
	{
	case eObjectName::MAIN_BACKGROUND:
		m_imageIndex = IMAGE_MAIN_BACKGROUND;
		m_moving = false;
		break;	
	
	case eObjectName::STAGE1_BACKGROUND:
		m_imageIndex = IMAGE_STAGE1_BACKGROUND;
		m_moving = true;
		break;	
	
	case eObjectName::STAGE2_BACKGROUND:
		m_imageIndex = IMAGE_STAGE2_BACKGROUND;
		m_moving = true;
		break;	
	
	case eObjectName::STAGE3_BACKGROUND:
		m_imageIndex = IMAGE_STAGE3_BACKGROUND;
		m_moving = true;
		break;

	case eObjectName::SNAKE_BACKGROUND:
		m_imageIndex = IMAGE_SNAKEPLANET_BACKGROUND;
		m_moving = false;
		break;

	case eObjectName::STORY_BACKGROUND:
		m_imageIndex = IMAGE_STORYPLANET_BACKGROUND;
		m_moving = false;
		break;
	}
}
