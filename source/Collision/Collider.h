#pragma once

#include <LFCommon.h>
#include <unordered_map>
#include <memory>
#include <Collision/AABB.h>

namespace LemonFizzx 
{
	enum class ColliderType {
		None = 0x0,
		Circle = 0x1,
		Polygon2D = 0x2, 
	};

	template <class T, class P>
	using CollisionFunc = bool (T::*)(const P&);
	
	class CollisionFunctionBase
	{
	public:
		virtual bool Invoke() = 0;
	};

	template <class ColliderClass, class OtherCollider>
	class CollisionFunction : public CollisionFunctionBase
	{
	public:
		CollisionFunction(CollisionFunc<ColliderClass, OtherCollider> function) : m_function(function) {}
		virtual bool Invoke() override
		{
			return m_function();
		}
	private:
		CollisionFunction() = delete;
		CollisionFunc<ColliderClass, OtherCollider> m_function;
	};

	LEMON_FIZZX_API class Collider {
		friend class LemonFizzx;
	public:
		virtual ~Collider() = default;
		virtual bool CheckCollision(Collider* other);

		const std::string& GetName() const { return m_name; }

	protected:
		virtual void Init() = 0;
		virtual void Update() {};

		template <class ColliderClass, class OtherCollider>
		void RegisterCollisionFunction(ColliderType type, CollisionFunc<ColliderClass, OtherCollider> collisionFunction);
		const AABB& GetAABB() const { return m_aabb; }
		const glm::vec3& GetPosition() const { return m_position; }

	private:
		std::unordered_map<ColliderType, std::unique_ptr<CollisionFunctionBase>> m_collisionFunctions;
		ColliderType m_colliderType = ColliderType::None;
		std::string m_name = "Collider";
		AABB m_aabb;

		glm::vec3 m_position = glm::vec3(0.0f);
	};

	template<class ColliderClass, class OtherCollider>
	inline void Collider::RegisterCollisionFunction(ColliderType type, CollisionFunc<ColliderClass, OtherCollider> collisionFunction)
	{
		if (m_collisionFunctions.find(type) != m_collisionFunctions.end())
		{
			return;
		}

		m_collisionFunctions[type] = new CollisionFunction<ColliderClass, OtherCollider>(collisionFunction);
	}
}