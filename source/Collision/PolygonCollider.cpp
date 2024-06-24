#include "PolygonCollider.h"

bool LemonFizzx::PolygonCollider::CheckCollision(PolygonCollider* other)
{
	float maxA = std::numeric_limits<float>::min();
	float minA = std::numeric_limits<float>::max();
	float maxB = std::numeric_limits<float>::min();
	float minB = std::numeric_limits<float>::max();

	std::vector<glm::vec2> normals;

	auto edgeNormal = [](const glm::vec2& v1, const glm::vec2& v2) -> glm::vec2 {
		return { -(v2.y - v1.y), v2.x - v1.x };
	};

	for (size_t i = 0; i < m_vertices.size(); ++i)
	{
		size_t j = (i + 1) % m_vertices.size();
		normals.push_back(edgeNormal(m_vertices[i], m_vertices[j]));
	}

	const std::vector<glm::vec2> vertices = other->GetVertices();

	for (size_t i = 0; i < vertices.size(); ++i) {
		size_t j = (i + 1) % vertices.size();
		normals.push_back(edgeNormal(vertices[i], vertices[j]));
	}

	for (const glm::vec2& axis : normals)
	{
		for (int i = 0; i < m_vertices.size(); i++)
		{
			float ab = glm::dot(axis, m_vertices[i]);
			float bb = glm::dot(axis, axis);

			glm::vec2 proj = (ab / bb) * axis;
			float magnitude = glm::length(proj);

			if (magnitude > maxA)
			{
				maxA = magnitude;
			}

			if (magnitude < minA)
			{
				minA = magnitude;
			}
		}

		for (int i = 0; i < other->m_vertices.size(); i++)
		{
			float ab = glm::dot(axis, other->m_vertices[i]);
			float bb = glm::dot(axis, axis);

			glm::vec2 proj = (ab / bb) * axis;
			float magnitude = glm::length(proj);

			if (magnitude > maxB)
			{
				maxB = magnitude;
			}

			if (magnitude < minB)
			{
				minB = magnitude;
			}
		}
	}

	// Check intersection
	if (maxA >= minB && minA <= maxB)
	{
		return true;
	}

	return false;
}
