#pragma once
#include <LFCommon.h>
#include <Collision/AABB.h>
#include <Collision/Collider.h>
#include <set>

namespace LemonFizzx
{
	LEMON_FIZZX_API class AABBNode
	{
	private:
		AABBNode* m_Parent = nullptr;
		std::weak_ptr<AABBNode> m_Left;
		std::weak_ptr<AABBNode> m_Right;
	};

	LEMON_FIZZX_API class AABBLeaf : public AABBNode
	{
	private:
		std::weak_ptr<Collider> m_collider;
	};

	LEMON_FIZZX_API class AABBBranch : public AABBNode
	{
	private:
		AABB m_AABB;
	};

	LEMON_FIZZX_API class AABBTree
	{
	public:
		void Insert(std::shared_ptr<Collider> collider);
	private:
		std::set<std::shared_ptr<AABB>> m_aabbs;
		std::weak_ptr<AABBNode> m_root;
	};
}