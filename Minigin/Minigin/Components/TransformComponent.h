#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable: 4201)
#include "glm/glm.hpp"
#pragma warning(pop)

namespace JKEngine
{

	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(glm::fvec3 pos = { 0.f, 0.f, 0.f });

		void Init() override;
		void Update(float deltaTime) override;
		void FixedUpdate(const float SPerUpdate) override;
		void Render() const override;

		const glm::fvec3& GetPosition() const;
		void SetPosition(const float x,const float y,const float z);

		const float& GetRotation() const { return m_Angle; }
		void SetAngle(float angle);

	private:
		friend class PhysicsComponent;
		glm::fvec3 m_Position;
		float m_Angle;
	};

}
