#pragma once

#include <LFCommon.h>

namespace LemonFizzx
{
	LEMON_FIZZX_API class AABB
	{

	private:
		bool CheckIntersection(const AABB& other) const;
		glm::vec3 m_min;
		glm::vec3 m_max;
	};
}