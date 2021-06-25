#include "myaabb.h"

namespace LM {

	bool MyAABB::LinesIntersect(const glm::vec2 &first, const glm::vec2 &second)
	{
		if (first.x > second.x && first.x < second.y ||
			first.y > second.x && first.y < second.y ||
			second.x > first.x && second.x < first.y ||
			second.y > first.x && second.y < first.y ||
			first.x == second.x && first.y == second.y)
			return true;
		return false;
	}

	bool MyAABB::Intersection(const MyAABB &other) {
		glm::vec2 other_MinExtents = other.GetMinExtents();
		glm::vec2 other_MaxExtents = other.GetMaxExtents();


		/*if (LinesIntersect(glm::vec2(m_MinExtents.x, m_MaxExtents.x), glm::vec2(other_MinExtents.x, other_MaxExtents.x)) &&
			LinesIntersect(glm::vec2(m_MinExtents.y, m_MaxExtents.y), glm::vec2(other_MinExtents.y, other_MaxExtents.y)))*/
		if (m_MaxExtents.x < other_MinExtents.x ||
			other_MaxExtents.x < m_MinExtents.x ||
			m_MaxExtents.y < other_MinExtents.y ||
			other_MaxExtents.y < m_MinExtents.y) {
			drawAABB(other);
			return false;
		}
		else
		{
			glm::vec2 response(0, 0);
			if (m_MaxExtents.x - other_MinExtents.x < other_MaxExtents.x - m_MinExtents.x) response.x = -(m_MaxExtents.x - other_MinExtents.x);
			else response.x = other_MaxExtents.x - m_MinExtents.x;
			if (m_MaxExtents.y - other_MinExtents.y < other_MaxExtents.y - m_MinExtents.y) response.y = -(m_MaxExtents.y - other_MinExtents.y);
			else response.y = other_MaxExtents.y - m_MinExtents.y;
			if (abs(response.x) / (m_MaxExtents.x - m_MinExtents.x) <= abs(response.y) / (m_MaxExtents.y - m_MinExtents.y)) response.y = 0;
			else response.x = 0;
			moveAABB(response);
			drawAABB(other);
			return true;
		}
	}

	const void MyAABB::drawAABB(const MyAABB &other) const
	{
		glm::vec2 other_MinExtents = other.GetMinExtents();
		glm::vec2 other_MaxExtents = other.GetMaxExtents();
		glBegin(GL_LINES);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glVertex3f(m_MinExtents.x, m_MinExtents.y, 0);
		glVertex3f(m_MaxExtents.x, m_MinExtents.y, 0);

		glVertex3f(m_MaxExtents.x, m_MinExtents.y, 0);
		glVertex3f(m_MaxExtents.x, m_MaxExtents.y, 0);

		glVertex3f(m_MaxExtents.x, m_MaxExtents.y, 0);
		glVertex3f(m_MinExtents.x, m_MaxExtents.y, 0);

		glVertex3f(m_MinExtents.x, m_MaxExtents.y, 0);
		glVertex3f(m_MinExtents.x, m_MinExtents.y, 0);


		glVertex3f(other_MinExtents.x, other_MinExtents.y, 0);
		glVertex3f(other_MaxExtents.x, other_MinExtents.y, 0);

		glVertex3f(other_MaxExtents.x, other_MinExtents.y, 0);
		glVertex3f(other_MaxExtents.x, other_MaxExtents.y, 0);

		glVertex3f(other_MaxExtents.x, other_MaxExtents.y, 0);
		glVertex3f(other_MinExtents.x, other_MaxExtents.y, 0);

		glVertex3f(other_MinExtents.x, other_MaxExtents.y, 0);
		glVertex3f(other_MinExtents.x, other_MinExtents.y, 0);

		glEnd();
	}
}