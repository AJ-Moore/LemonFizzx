#include "AABBTree.h"

namespace LemonFizzx
{
	void AABBTree::Insert(std::shared_ptr<Collider> collider)
	{
		if (m_colliders.contains(collider))
		{
			Log(CitrusCore::Logger::DEBUG, "Collider already registered. [%s]", __FUNCTION__);
			return;
		}

		// Create a leaf node for the collider
		std::shared_ptr<AABBLeaf> leaf = std::make_shared<AABBLeaf>(collider);

		// Insert the leaf into the tree recursively
		InsertLeaf(m_root, leaf);
	}

	bool AABBTree::CheckExpired(std::shared_ptr<AABBNode> node)
	{
		if (node->m_nodeType != NodeType::Leaf)
		{
			return false;
		}

		AABBLeaf* leaf = (AABBLeaf*)node.get();

		// Check if collider has been removed 
		if (leaf->GetCollider().expired())
		{
			// Remove node here!
			Log(CitrusCore::Logger::DEBUG, "Node expired, todo: remove expired node from tree!!");
			return true;
		}

		return false;
	}

	void AABBTree::ResizeNode(AABBNode* node)
	{
		if (node == nullptr)
		{
			return;
		}

		if (node->m_nodeType != NodeType::Branch)
		{
			return;
		}

		AABBBranch* branch = static_cast<AABBBranch*>(node);

		if (node->GetLeft() != nullptr && node->GetRight() != nullptr)
		{
			const AABB left = node->GetLeft()->GetAABB();
			const AABB right = node->GetRight()->GetAABB();

			const glm::vec3 leftMin = left.GetMin();
			const glm::vec3 leftMax = left.GetMax();
			const glm::vec3 rightMin = right.GetMin(); 
			const glm::vec3 rightMax = right.GetMax();

			glm::vec3 min = glm::vec3(std::min(leftMin.x, rightMin.x),
				std::min(leftMin.y, rightMin.y),
				std::min(leftMin.z, rightMin.z));

			glm::vec3 max = glm::vec3(std::max(leftMax.x, rightMax.x),
				std::min(leftMax.y, rightMax.y),
				std::min(leftMax.z, rightMax.z));

			branch->m_AABB.SetMin(min);
			branch->m_AABB.SetMax(max);
		}
		else
		{
			if (node->GetLeft() != nullptr)
			{
				branch->m_AABB.SetMin(node->GetLeft()->GetAABB().GetMin());
				branch->m_AABB.SetMax(node->GetLeft()->GetAABB().GetMax());
			}

			if (node->GetRight() != nullptr)
			{
				branch->m_AABB.SetMin(node->GetRight()->GetAABB().GetMin());
				branch->m_AABB.SetMax(node->GetRight()->GetAABB().GetMax());
			}
		}
		
		if (!node->m_parent.expired())
		{
			ResizeNode(node->m_parent.lock().get());
		}
	}

	void AABBTree::InsertLeaf(std::shared_ptr<AABBNode> node, std::shared_ptr<AABBLeaf> leaf)
	{
		// If root node is null, set the root to the leaf
		if (m_root == nullptr)
		{
			m_root = leaf;
			return;
		};
		
		// Check whether colliders expired/removed and repair tree if so(todo)
		if (CheckExpired(node) || CheckExpired(node->GetLeft()) || CheckExpired(node->GetRight()))
		{
			return;
		}

		std::shared_ptr<AABBNode> left = node->GetLeft();
		std::shared_ptr<AABBNode> right = node->GetRight();

		// If has empty child node, use empty node
		if (left == nullptr || right == nullptr)
		{
			if (node->GetLeft() == nullptr)
			{
				node->m_left = leaf;
				leaf->m_parent = node;
				ResizeNode(leaf->m_parent.lock().get());
			}

			if (node->GetRight() == nullptr)
			{
				node->m_right = leaf;
				leaf->m_parent = node;
				ResizeNode(leaf->m_parent.lock().get());
			}
		}
	}
}
