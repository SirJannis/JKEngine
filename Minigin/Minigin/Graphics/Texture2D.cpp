#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

JKEngine::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

void JKEngine::Texture2D::SetTexture(SDL_Texture* newTexture)
{
	SDL_DestroyTexture(m_Texture);
	m_Texture = newTexture;
}

SDL_Texture* JKEngine::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

JKEngine::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
