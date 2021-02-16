#include "MiniginPCH.h"
#include "TransformComponent.h"

JKEngine::TransformComponent::TransformComponent(glm::fvec3 pos)
	:m_Position{ pos }
	, m_Angle{}
{
}

void JKEngine::TransformComponent::Update(const float msPerSec)
{
	UNREFERENCED_PARAMETER(msPerSec);
}

void JKEngine::TransformComponent::Render() const
{
}

const glm::fvec3& JKEngine::TransformComponent::GetPosition() const
{
	return m_Position;
}

void JKEngine::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void JKEngine::TransformComponent::SetAngle(float angle)
{
	m_Angle = angle;
}