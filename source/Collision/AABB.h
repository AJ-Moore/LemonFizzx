#pragma once

#include <LFCommon.h>

namespace LemonFizzx
{
	LEMON_FIZZX_API class AABB
	{
	public:
		void SetMin(const glm::vec3& min) { m_min = min; }
		void SetMax(const glm::vec3& max) { m_max = max; }
		bool CheckIntersection(const AABB& other) const;

		const glm::vec3& GetMin() const { return m_min; }
		const glm::vec3& GetMax() const { return m_max; }
	private:
		glm::vec3 m_min;
		glm::vec3 m_max;
	};
}