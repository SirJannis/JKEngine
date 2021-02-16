#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "../Scene/GameObject.h"
#include "TextComponent.h"

void JKEngine::FPSComponent::Update(const float msPerFrame)
{
	m_DeltaTime += msPerFrame;
	m_FPS++;
	if (m_DeltaTime >= 1)
	{
		m_DeltaTime--;
		m_pGameObject->GetComponent<TextComponent>()->SetText("FPS: " + std::to_string(m_FPS));
		m_FPS = 0;
	}
}

void JKEngine::FPSComponent::Render() const
{
}