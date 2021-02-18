#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "../Scene/GameObject.h"
#include "TextComponent.h"

JKEngine::FPSComponent::FPSComponent()
	:m_Interval(1)
{
	
}

JKEngine::FPSComponent::~FPSComponent()
{
	m_pTextComponent = nullptr;
}

void JKEngine::FPSComponent::Init()
{
	m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();
}

void JKEngine::FPSComponent::Update(float deltaTime)
{
	m_DeltaTime += deltaTime;
	//make this an average fps over all collected deltatimes instead of just this
	m_FPS = static_cast<int>(m_Interval / deltaTime);
	if (m_DeltaTime >= static_cast<float>(m_Interval))
	{
		m_pTextComponent->SetText("FPS: " + std::to_string(m_FPS));
		m_DeltaTime-= static_cast<float>(m_Interval);
	}
}

void JKEngine::FPSComponent::FixedUpdate(const float SPerUpdate)
{
	UNREFERENCED_PARAMETER(SPerUpdate);
}

void JKEngine::FPSComponent::Render() const
{
}