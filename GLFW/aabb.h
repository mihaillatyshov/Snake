#pragma once

#include <glm.hpp>
#include "intersectdata.h"

namespace LM {

	class AABB
	{
	private:
		const glm::vec3 m_MinExtents;
		const glm::vec3 m_MaxExtents;

	private:
		float MaxVal(const glm::vec3 &vector) const;
		const glm::vec3 &Max(const glm::vec3 &first, const glm::vec3 &second) const;
	public:
		AABB(const glm::vec3 &minExtents, const glm::vec3 &maxExtents):
		m_MinExtents(minExtents),
		m_MaxExtents(maxExtents){}

		IntersectData IntersectAABB(const AABB &other) const;

		inline const glm::vec3 GetMinExtents() const { return m_MinExtents; }
		inline const glm::vec3 GetMaxExtents() const { return m_MaxExtents; }
	};

}