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

	m_CanCollide = false; // [TW] 콜라이더를 우선적으로 해제. PutCollider를 통해 나중에 추가하려면 추가되는 것.
	m_ColliderType = eColType::NONE;
	isPhysicsOn = false;
}

GameObject::GameObject(eObjectTag tag, eObjectName name, Transform transform)
	: m_tag(tag), m_name(name), m_pTransform(nullptr), m_imageIndex(0), m_pCollider(nullptr), isCollided(false)
{
	m_pTransform = new Transform(transform.GetPosition(), transform.GetRotation(), transform.GetScale());

	m_CanCollide = false; // [TW] 콜라이더를 우선적으로 해제. PutCollider를 통해 나중에 추가하려면 추가되는 것.
	m_ColliderType = eColType::NONE;
	isPhysicsOn = false;
}

GameObject::~GameObject()
{
	delete m_pTransform;
	
	if (m_pCollider != nullptr) // 콜라이더가 nullptr이 아니면 삭제, RAII.
	{
		delete m_pCollider;
	}

	if (m_pBody != nullptr) // 바디가 nullptr이 아니면 삭제, RAII.
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
		//const 참조라 값복사 발생X.
		m_pCollider = new BoxCollider(*(this->GetPTransform()), imageIndex);
	}
	else if (colliderType == eColType::CIRCLE)
	{
		m_pCollider = new CircleCollider(*(this->GetPTransform()), imageIndex);
	}
}

//[TW] 뻑간다.
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

