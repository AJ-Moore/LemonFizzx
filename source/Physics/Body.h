#pragma once

#include <LFCommon.h>

namespace LemonFizzx {
	class Body {
	public:
		virtual ~Body() {}

		void SetPosition(const glm::vec3& position) { m_position = position; }
		const glm::vec3& GetPosition() const { return m_position; }
	private:
		glm::vec3 m_position;
	};
}