#pragma once
#include "BaseComponent.h"
#include <vector>
#pragma warning(push)
#pragma warning (disable: 4201)
#include "glm/common.hpp"
#pragma warning(pop)
namespace JKEngine
{
	class Renderer;
	class TransformComponent;
	class Texture2D;
	struct RenderTexture
	{
		Texture2D* Texture;
		int DrawWidth;
		int DrawHeight;
		bool IsMirrored;
		glm::fvec2 Pivot;
		glm::fvec2 Offset;
		glm::fvec2 SrcPos;
		glm::fvec2 SrcDim;
		float Angle;
	};
	
	class RenderComponent final : public BaseComponent
	{
	public:
		~RenderComponent() override;

		void Init() override;
		void Update(const float msPerFrame) override;
		void Render() const override;

		void AddTexture(Texture2D* text, const int drawWidth = 0, const int drawHeight = 0, const bool isMirrored = false, const glm::fvec2& pivot = { .5f, .5f }, const glm::fvec2& offset = { 0.f, 0.f }, const glm::fvec2& srcPos = { 0.f, 0.f }, const glm::fvec2& srcDim = { 1.f, 1.f }, const float angle = 0.f);
	private:

		std::vector<RenderTexture> m_Textures;
		TransformComponent* m_pTransformComponent;
		Renderer* m_pRendererInstance;
	};
}