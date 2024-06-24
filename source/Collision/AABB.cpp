#include "AABB.h"

bool LemonFizzx::AABB::CheckIntersection(const AABB& other) const
{
    return (m_min.x <= other.m_max.x && m_max.x >= other.m_min.x) &&
		   (m_min.y <= other.m_max.y && m_max.y >= other.m_min.y) &&
		   (m_min.z <= other.m_max.z && m_max.z >= other.m_min.z);
}
