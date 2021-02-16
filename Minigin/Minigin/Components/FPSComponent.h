#pragma once
#include "BaseComponent.h"
namespace JKEngine
{
	class FPSComponent final : public BaseComponent
	{
	public:
		void Update(const float msPerFrame) override;
		void Render() const override;

	private:
		float m_DeltaTime;
		int m_FPS;
	};
}
