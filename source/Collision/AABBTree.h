#pragma once
#include <LFCommon.h>
#include <Collision/AABB.h>
#include <Collision/Collider.h>
#include <set>

namespace LemonFizzx
{
	LEMON_FIZZX_API enum NodeType
	{
		Leaf = 0x1,
		Branch = 0x2,
		None = 0x0
	};

	LEMON_FIZZX_API class AABBNode
	{
		friend class AABBTree;
	public:
		std::shared_ptr<AABBNode> GetLeft() { return m_left; }
		std::shared_ptr<AABBNode> GetRight() { return m_right; }
		virtual const AABB& GetAABB() = 0;

	protected:
		NodeType m_nodeType = NodeType::None;
		std::weak_ptr<AABBNode> m_parent;

		std::shared_ptr<AABBNode> m_left;
		std::shared_ptr<AABBNode> m_right;

		// AVL tree 
		int m_height = 1;
	};

	LEMON_FIZZX_API class AABBLeaf : public AABBNode
	{
		friend class AABBTree;
	public:
		AABBLeaf(std::shared_ptr<Collider> collider) : m_collider(collider) { m_nodeType = NodeType::Leaf; }
		std::weak_ptr<Collider> GetCollider() { return m_collider; }
		virtual const AABB& GetAABB() override { return m_collider.lock()->GetAABB(); }
	private:
		AABBLeaf() = delete;
		std::weak_ptr<Collider> m_collider;
	};

	LEMON_FIZZX_API class AABBBranch : public AABBNode
	{
		friend class AABBTree;
	public:
		virtual const AABB& GetAABB() override { return m_AABB; }
		AABBBranch() { m_nodeType = NodeType::Branch; }
	private:
		AABB m_AABB;
	};

	LEMON_FIZZX_API class AABBTree
	{
	public:
		void Insert(std::shared_ptr<Collider> collider);
	private:
		void ResizeNode(AABBNode* node);
		void InsertLeaf(std::shared_ptr<AABBNode> node, std::shared_ptr<AABBLeaf> leaf);
		bool CheckExpired(std::shared_ptr<AABBNode> node);
		std::set<std::weak_ptr<Collider>> m_colliders;
		std::shared_ptr<AABBNode> m_root;
	};
}