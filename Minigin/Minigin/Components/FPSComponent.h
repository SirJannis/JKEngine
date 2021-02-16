#pragma once
#include "BaseComponent.h"
namespace JKEngine
{

	class TextComponent;
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent();
		~FPSComponent() override;
		void Init() override;
		void Update(const float msPerFrame) override;
		void Render() const override;

	private:
		float m_DeltaTime;
		int m_FPS;
		TextComponent* m_pTextComponent;
	};
}
