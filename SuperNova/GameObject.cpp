#include "GameObject.h"
#include "RenderSystem.h"
#include "Transform.h"
#include "Collider.h"
#include "BoxCollider.h";
#include "CircleCollider.h"
#include "Scene.h"

using namespace std;

GameObject::GameObject(eObjectTag tag, eObjectName name, Transform transform, int imageIndex)
	: m_tag(tag), m_name(name), m_pTransform(nullptr), m_imageIndex(imageIndex), m_pCollider(nullptr), isCollided(false)
{
	m_pTransform = new Transform(transform.GetPosition(), transform.GetRotation(), transform.GetScale());

	m_CanCollide = false; // [TW] �ݶ��̴��� �켱������ ����. PutCollider�� ���� ���߿� �߰��Ϸ��� �߰��Ǵ� ��.
	m_ColliderType = eColType::NONE;
	isPhysicsOn = false;
}

GameObject::GameObject(eObjectTag tag, eObjectName name, Transform transform)
	: m_tag(tag), m_name(name), m_pTransform(nullptr), m_imageIndex(0), m_pCollider(nullptr), isCollided(false)
{
	m_pTransform = new Transform(transform.GetPosition(), transform.GetRotation(), transform.GetScale());

	m_CanCollide = false; // [TW] �ݶ��̴��� �켱������ ����. PutCollider�� ���� ���߿� �߰��Ϸ��� �߰��Ǵ� ��.
	m_ColliderType = eColType::NONE;
	isPhysicsOn = false;
}

GameObject::~GameObject()
{
	delete m_pTransform;
	
	if (m_pCollider != nullptr) // �ݶ��̴��� nullptr�� �ƴϸ� ����, RAII.
	{
		delete m_pCollider;
	}

	if (m_pBody != nullptr) // �ٵ� nullptr�� �ƴϸ� ����, RAII.
	{
		delete m_pBody;
	}
}

void GameObject::Start()
{
	//Tlqfus~
}

void GameObject::Update()
{
	//
}

void GameObject::LateUpdate()
{
	//
}


void GameObject::Render()
{
	//RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
	
}

Transform* GameObject::GetPTransform()
{
	return m_pTransform;
}

Collider* GameObject::GetPCollider()
{
	return m_pCollider;
}

Body* GameObject::GetPBody()
{
	return m_pBody;
}

GameObject* GameObject::FetchPlayerObject()
{
	fixedPlayerObject = belongScene->FindObjectInScene(eObjectName::PLAYER);
	return fixedPlayerObject;
}

void GameObject::FixPlayerSafeInUpdate()
{
	if (fixedPlayerObject == nullptr)
	{
		fixedPlayerObject = belongScene->FindObjectInScene(eObjectName::PLAYER);
	}
}

void GameObject::PutCollider(eColType colliderType, int imageIndex)
{
	m_CanCollide = true;
	m_ColliderType = colliderType;

	if (colliderType == eColType::BOX)
	{
		//const ������ ������ �߻�X.
		m_pCollider = new BoxCollider(*(this->GetPTransform()), imageIndex);
	}
	else if (colliderType == eColType::CIRCLE)
	{
		m_pCollider = new CircleCollider(*(this->GetPTransform()), imageIndex);
	}
}

//[TW] ������.
void GameObject::PutBody(int mass)
{
	isPhysicsOn = true;

	this->m_pBody = new Body(mass, m_pTransform);
}

void GameObject::SetColState(bool state)
{
	m_CanCollide = state;
}

bool GameObject::GetColState()
{
	return m_CanCollide;
}

eColType GameObject::GetColType()
{
	return m_ColliderType;
}

void GameObject::SetPhysicsState(bool state)
{
	isPhysicsOn = state;
}

bool GameObject::GetPhysicsState()
{
	return isPhysicsOn;
}

void GameObject::AddForce(Vec2 force)
{
	if (this->GetPBody() != nullptr)
	{
		this->GetPBody()->AddForce(force);
	}
}

void GameObject::TurnOffCollider()
{

	this->m_CanCollide = false;
}

