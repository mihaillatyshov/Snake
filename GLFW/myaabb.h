#pragma once

#include <GL/glew.h>
#include <glm.hpp>
#include <cmath>

namespace LM {

	class MyAABB
	{
	private:
		glm::vec2 m_MinExtents;
		glm::vec2 m_MaxExtents;
	public:
		bool Intersection(const MyAABB &other);

		inline const glm::vec2 GetMinExtents() const { return m_MinExtents; }
		inline const glm::vec2 GetMaxExtents() const { return m_MaxExtents; }
		inline const void moveAABB(const glm::vec2 &velocity) { m_MinExtents += velocity; m_MaxExtents += velocity; }
		inline const void setAABB(const glm::vec2 &position) {	glm::vec2 res = m_MaxExtents - m_MinExtents;
																m_MinExtents = position; m_MaxExtents = res + position; }
		MyAABB(const glm::vec2 &minExtents, const glm::vec2 &maxExtents) :
			m_MinExtents(minExtents),
			m_MaxExtents(maxExtents) {}
	private:
		bool LinesIntersect(const glm::vec2 &first, const glm::vec2 &second);
		const void drawAABB(const MyAABB &other) const;
	};

}