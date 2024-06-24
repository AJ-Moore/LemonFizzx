
#include <Collision/CircleCollider.h>

namespace LemonFizzx
{
	bool CircleCollider::CheckCollision(const CircleCollider& other)
	{
		return false;
	}

	void CircleCollider::Init()
	{
		RegisterCollisionFunction<CircleCollider, CircleCollider>(ColliderType::Circle, &CircleCollider::CheckCollision);
	}
}
