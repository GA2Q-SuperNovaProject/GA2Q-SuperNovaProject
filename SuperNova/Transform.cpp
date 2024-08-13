#include "Transform.h"
#include "Math.h"
#include <math.h>

Transform::Transform(Vec2 position, float rotation, Vec2 scale) 
	: m_Position(position), m_Rotation(rotation), m_Scale(scale)
{
	//
}

Transform::~Transform()
{
	//
}

float Transform::GetRotation() const
{
	return fmod(m_Rotation, 360.0f);
}
