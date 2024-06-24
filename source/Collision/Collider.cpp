#include "Collider.h"

bool LemonFizzx::Collider::CheckCollision(Collider* other)
{
    auto collisionFunction = m_collisionFunctions.find(other->m_colliderType);

	if (collisionFunction != m_collisionFunctions.end())
	{
		return collisionFunction->second->Invoke();
	}

	printf("Unable to find collision function for colliders [%s] and [%s]", m_name.c_str(), other->GetName().c_str());
	return false; 
}
