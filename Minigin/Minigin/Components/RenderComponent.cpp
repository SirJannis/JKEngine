#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Renderer.h"
#include "../Scene/GameObject.h"
#include "SDL.h"
#pragma warning(push)
#pragma warning (disable: 4201)
#include "glm/gtx/rotate_vector.hpp"
#pragma warning(pop)

JKEngine::RenderComponent::~RenderComponent()
{
	m_pTransformComponent = nullptr;
	m_pRendererInstance = nullptr;
}

void JKEngine::RenderComponent::Init()
{
	m_pTransformComponent = m_pGameObject->GetComponent<TransformComponent>();
	m_pRendererInstance = Renderer::GetInstance();
}

void JKEngine::RenderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void JKEngine::RenderComponent::FixedUpdate(const float SPerUpdate)
{
	UNREFERENCED_PARAMETER(SPerUpdate);
}

void JKEngine::RenderComponent::Render() const
{
	for (const RenderTexture& texture : m_Textures)
	{
		const glm::fvec2& pos = m_pTransformComponent->GetPosition();
		SDL_Rect destRect{ int(pos.x), int(pos.y) };
		SDL_QueryTexture(texture.Texture->GetSDLTexture(), nullptr, nullptr, &destRect.w, &destRect.h);

		SDL_Rect srcRect{ int(texture.SrcPos.x * destRect.w), int(texture.SrcPos.y * destRect.h) , int(texture.SrcDim.x * destRect.w) , int(texture.SrcDim.y * destRect.h) };

		if (texture.DrawWidth != 0 && texture.DrawHeight != 0)
		{
			destRect.w = texture.DrawWidth;
			destRect.h = texture.DrawHeight;
		}

		SDL_Point pivot{ int(texture.Pivot.x * destRect.w), int(texture.Pivot.y * destRect.h) };
		glm::fvec2 offset{ texture.Offset.x * destRect.w, texture.Offset.y * destRect.h };

		offset = glm::rotate(offset, m_pTransformComponent->GetRotation() * float(M_PI) / 180.f);

		destRect.x += int(offset.x) - pivot.x;
		destRect.y += int(offset.y) + pivot.y;

		m_pRendererInstance->RenderTexture(*texture.Texture, &destRect, &srcRect, m_pTransformComponent->GetRotation() + texture.Angle, pivot, texture.IsMirrored);

	}
}

void JKEngine::RenderComponent::AddTexture(Texture2D* text, const int drawWidth, const int drawHeight, const bool isMirrored, const glm::fvec2& pivot, const glm::fvec2& offset, const glm::fvec2& srcPos, const glm::fvec2& srcDim, const float angle)
{
	m_Textures.push_back({ text, drawWidth, drawHeight, isMirrored, pivot, offset, srcPos, srcDim, angle });
}


