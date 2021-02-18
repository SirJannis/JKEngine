#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "../Scene/GameObject.h"
#include "TextComponent.h"

JKEngine::FPSComponent::FPSComponent()
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

void JKEngine::FPSComponent::Update(const float SPerUpdate)
{
	m_DeltaTime += SPerUpdate;
	m_FPS++;
	if (m_DeltaTime >= 1)
	{
		m_DeltaTime--;
		m_pTextComponent->SetText("FPS: " + std::to_string(m_FPS));
		m_FPS = 0;
	}
}

void JKEngine::FPSComponent::Render() const
{
}