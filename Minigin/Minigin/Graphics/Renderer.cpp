#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "../Managers/SceneManager.h"
#include "Texture2D.h"
//Imgui think about moving this
#include "imgui.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void JKEngine::Renderer::Init(SDL_Window * window)
{
	m_pWindow = window;
	m_pRenderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	//Imgui Init, think about moving this
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
	
}

void JKEngine::Renderer::Render() const
{
	SDL_RenderClear(m_pRenderer);

	SceneManager::GetInstance()->Render();

	//Imgui demo window, move this somewhere else!
	bool showdemo = true;
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();
	if (showdemo)
		ImGui::ShowDemoWindow(&showdemo);
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_pRenderer);
}

void JKEngine::Renderer::Destroy()
{
	//Imgui Destroy, think about destroying it
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	if (m_pRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

//void JKEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
//{
//	SDL_Rect dst;
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
//}
//
//void JKEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
//{
//	SDL_Rect dst;
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	dst.w = static_cast<int>(width);
//	dst.h = static_cast<int>(height);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
//}

void JKEngine::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect* dstRect, const SDL_Rect* srcRect, const float angle, const SDL_Point& pivot, const bool isMirroredHorizontal) const
{
	int w;
	int h;
	SDL_GetRendererOutputSize(m_pRenderer, &w, &h);
	SDL_Rect destRect{ dstRect->x, h - dstRect->y, dstRect->w, dstRect->h };
	SDL_RenderCopyEx(m_pRenderer, texture.GetSDLTexture(), srcRect, &destRect, angle, &pivot, SDL_RendererFlip(isMirroredHorizontal));

}

void JKEngine::Renderer::RenderLine(const SDL_Point& p1, const SDL_Point& p2, const SDL_Point& pivot, const SDL_Color& color)
{
	int w;
	int h;
	SDL_GetRendererOutputSize(m_pRenderer, &w, &h);
	SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(m_pRenderer, p1.x, h - (2 * pivot.y - p1.y), p2.x, h - (2 * pivot.y - p2.y));
}