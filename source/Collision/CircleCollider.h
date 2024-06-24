#pragma once

#include <Collision/Collider.h>

namespace LemonFizzx {
	class CircleCollider : public Collider {
		friend class LemonFizzx;
	public:
		CircleCollider(float radius) : m_radius(radius) {}
		virtual ~CircleCollider() = default;

		virtual bool CheckCollision(const CircleCollider& other);
	protected:
		virtual void Init() override;
		virtual void Update() {};

		float GetRadius() const { return m_radius; }
		void SetRadius(float radius) { m_radius = radius; }
	private:
		float m_radius = 0.0f;
	};
}