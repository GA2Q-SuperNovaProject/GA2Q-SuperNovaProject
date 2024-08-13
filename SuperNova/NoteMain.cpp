#include "NoteMain.h"
#include "Debug.h"
#include "Camera.h"
#include "InputManager.h"
#include "MouseInputManager.h"
#include "Vec2.h"
#include "RenderSystem.h"
#include "Transform.h"

using namespace std;

NoteMain::NoteMain(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform), temp(transform.GetPosition())
{

}

NoteMain::~NoteMain()
{

}

void NoteMain::Update()
{
	m_pTransform->SetPosition(Camera::GeInstance().WorldToCameraPOINT(temp));
}

void NoteMain::Render()
{
	RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
}
