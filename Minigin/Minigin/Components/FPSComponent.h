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
		void Update(float deltaTime) override;
		void FixedUpdate(const float SPerUpdate) override;
		void Render() const override;

	private:
		float m_DeltaTime;
		int m_FPS;
		int m_Interval;
		TextComponent* m_pTextComponent;
	};
}
