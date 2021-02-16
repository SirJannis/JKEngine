#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../Graphics/Renderer.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Font.h"

JKEngine::ResourceManager::~ResourceManager()
{
	for (Texture2D* pTexture : m_Textures)
	{
		SafeDelete(pTexture);
	}
	for (Font* pFont : m_Fonts)
	{
		SafeDelete(pFont);
	}
}

void JKEngine::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

JKEngine::Texture2D* JKEngine::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = m_DataPath + file;
	for (Texture2D* pTexture : m_Textures)
	{
		if (pTexture->GetPath() == fullPath)
			return pTexture;
	}
	auto texture = IMG_LoadTexture(Renderer::GetInstance()->GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	m_Textures.push_back(new Texture2D(texture));
	m_Textures.back()->SetPath(fullPath);
	return m_Textures.back();
}

JKEngine::Font* JKEngine::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	const auto fullPath = m_DataPath + file;
	for (Font* pFont : m_Fonts)
	{
		if (pFont->GetPath() == fullPath)
			return pFont;
	}
	m_Fonts.push_back(new Font(fullPath, size));
	return m_Fonts.back();
}
