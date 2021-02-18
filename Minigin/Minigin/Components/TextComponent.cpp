#include "MiniginPCH.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h>

#include "TextComponent.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Font.h"
#include "../Graphics/Texture2D.h"
#include "../Scene/GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

void JKEngine::TextComponent::Init()
{
	m_pRenderInstance = Renderer::GetInstance();
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
}

void JKEngine::TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void JKEngine::TextComponent::FixedUpdate(const float SPerUpdate)
{
	UNREFERENCED_PARAMETER(SPerUpdate);
}

void JKEngine::TextComponent::Render() const
{
	glm::vec2 pos{ m_pTransformComponent->GetPosition() };
	SDL_Rect dstRect{ static_cast<int>(pos.x), static_cast<int>(pos.y) };
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &dstRect.w, &dstRect.h);
	SDL_Point pivot = { int(m_Pivot.x * dstRect.w), int(m_Pivot.y * dstRect.h) };
	dstRect.x += -pivot.x + int(m_Offset.x);
	dstRect.y += pivot.y + int(m_Offset.y);
	m_pRenderInstance->RenderTexture(*m_pTexture, &dstRect, nullptr, m_pGameObject->GetComponent<TransformComponent>()->GetRotation() + m_Angle, pivot, false);
}

JKEngine::TextComponent::TextComponent(const std::string& text, Font* pFont, SDL_Color color, const float angle, const glm::fvec2 pivot, const glm::fvec2 offset)
	: m_Text(text), m_pFont(pFont), m_pTexture(nullptr), m_Color(color), m_Angle{ angle }, m_Pivot{ pivot }, m_Offset{ offset }
{
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	//Constructor goes before init so here it is done with GetInstance since the local instance is still nullptr
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance()->GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_pTexture = new Texture2D(texture);
}

JKEngine::TextComponent::~TextComponent()
{
	SafeDelete(m_pTexture);
	m_pRenderInstance = nullptr;
	m_pTransformComponent = nullptr;
}


void JKEngine::TextComponent::SetText(const std::string& text)
{
	//if possible don't create a new surface and texture every time
	m_Text = text;
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(m_pRenderInstance->GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_pTexture->SetTexture(texture);
}

JKEngine::Texture2D* JKEngine::TextComponent::GetTexture() const
{
	return m_pTexture;
}
