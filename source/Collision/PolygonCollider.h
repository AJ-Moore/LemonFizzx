#pragma once

#include <LFCommon.h>
#include <Collision/Collider.h>

namespace LemonFizzx
{
	LEMON_FIZZX_API class PolygonCollider : public Collider
	{
	public:
		virtual bool CheckCollision(PolygonCollider* other);
		const std::vector<glm::vec2>& GetVertices() const { return m_vertices; }
	private:
		std::vector<glm::vec2> m_vertices;
	};
}