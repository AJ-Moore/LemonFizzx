#pragma once

#include "LFCommon.h"
#include <Collision/Collider.h>
#include <Collision/AABBTree.h>	

namespace LemonFizzx {
	class LEMON_FIZZX_API LemonFizz {
	public:
		LemonFizz() {}
		virtual ~LemonFizz() {}

	protected:
		virtual bool Init();
		virtual void Update();

		virtual void RegisterCollider(Collider* Collider);

		AABBTree m_AABBTree;
		//Datestamp m_physicsStep = 0;

	};
}
