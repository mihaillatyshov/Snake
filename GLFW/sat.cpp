#include "sat.h"
#include <GL/glew.h>

namespace LM {

	IntersectData Sat::IntersectSAT(const Sat &other) 
	{

		//glm::vec3 max = MaxValues(other);

#pragma region first
		glm::vec3 other_first = other.getFirstPoint();
		glm::vec3 other_second = other.getSecondPoint();
		glm::vec3 other_third = other.getThirdPoint();

		glm::vec3 max = MaxValues(	MaxValues(m_first, m_second, m_third),
									MaxValues(other_first, other_second, other_third));
#pragma endregion

#if 1
		glBegin(GL_LINES);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glVertex3f(m_first.x, m_first.y, m_first.z);
		glVertex3f(m_second.x, m_second.y, m_second.z);

		glVertex3f(m_second.x, m_second.y, m_second.z);
		glVertex3f(m_third.x, m_third.y, m_third.z);

		glVertex3f(m_third.x, m_third.y, m_third.z);
		glVertex3f(m_first.x, m_first.y, m_first.z);


		glVertex3f(other_first.x, other_first.y, other_first.z);
		glVertex3f(other_second.x, other_second.y, other_second.z);

		glVertex3f(other_second.x, other_second.y, other_second.z);
		glVertex3f(other_third.x, other_third.y, other_third.z);

		glVertex3f(other_third.x, other_third.y, other_third.z);
		glVertex3f(other_first.x, other_first.y, other_first.z);

		glEnd();

#endif
		// t1 t2
		// t2 t3
		// t3 t1
		//
		// o1 o2
		// o2 o3
		// o3 o1
#pragma region first
		std::vector<bool> Detection;

		glm::vec3 vector = unitVec(m_first, m_second);
		Detection.push_back(CheckVector(vector, other, max));
		//std::cout << vector.x << " " << vector.y << " " << vector.z << std::endl;

		vector = unitVec(m_second, m_third);
		Detection.push_back(CheckVector(vector, other, max));
		//std::cout << vector.x << " " << vector.y << " " << vector.z << std::endl;

		vector = unitVec(m_third, m_first);
		Detection.push_back(CheckVector(vector, other, max));
		//std::cout << vector.x << " " << vector.y << " " << vector.z << std::endl;

		vector = unitVec(other_first, other_second);
		Detection.push_back(CheckVector(vector, other, max));
		//std::cout << vector.x << " " << vector.y << " " << vector.z << std::endl;

		vector = unitVec(other_second, other_third);
		Detection.push_back(CheckVector(vector, other, max));
		//std::cout << vector.x << " " << vector.y << " " << vector.z << std::endl;

		vector = unitVec(other_third, other_first);
		Detection.push_back(CheckVector(vector, other, max));

		//std::cout << vector.x << " " << vector.y << " " << vector.z << std::endl;
		 

		//std::cout << min.x << " " << min.y << " " << min.z << std::endl;
		//std::cout << max.x << " " << max.y << " " << max.z << std::endl;

		for (unsigned int i = 0; i < Detection.size(); i++) {
			if (Detection[i] == false)
				return IntersectData(0, 0);
		}

		m_first -= m_velocity; m_second -= m_velocity; m_third -= m_velocity;
		m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		std::cout << "Collided!" << std::endl;
		return IntersectData(1, 0);
#pragma endregion
	}

	bool Sat::CheckVector(const glm::vec3 &vector, const Sat &other, const glm::vec3 &max)
	{
		glm::vec3 other_first = other.getFirstPoint();
		glm::vec3 other_second = other.getSecondPoint();
		glm::vec3 other_third = other.getThirdPoint();

		std::vector<float> points;

		if (vector.x != 0) {
			points.push_back(m_first.y + vector.y * (max.x - m_first.x));
			points.push_back(m_second.y + vector.y * (max.x - m_second.x));
			points.push_back(m_third.y + vector.y * (max.x - m_third.x));
			points.push_back(other_first.y + vector.y * (max.x - other_first.x));
			points.push_back(other_second.y + vector.y * (max.x - other_second.x));
			points.push_back(other_third.y + vector.y * (max.x - other_third.x));

#if 0

			glBegin(GL_LINES);
			glColor4f(0.0, 1.0, 0.0, 1.0);
			glVertex3f(max.x, MinFloat(points[0], points[1], points[2]), max.z);
			glVertex3f(max.x, MaxFloat(points[0], points[1], points[2]), max.z);

			glVertex3f(max.x, MinFloat(points[3], points[4], points[5]), max.z);
			glVertex3f(max.x, MaxFloat(points[3], points[4], points[5]), max.z);
			glEnd();

			glBegin(GL_LINES);
			glColor4f(0.0, 1.0, 0.0, 1.0);
			glVertex3f(m_first.x, m_first.y, m_first.z);
			glVertex3f(max.x, points[0], max.z);

			glVertex3f(m_second.x, m_second.y, m_second.z);
			glVertex3f(max.x, points[1], max.z);

			glVertex3f(m_third.x, m_third.y, m_third.z);
			glVertex3f(max.x, points[2], max.z);

			glVertex3f(other_first.x, other_first.y, other_first.z);
			glVertex3f(max.x, points[3], max.z);

			glVertex3f(other_second.x, other_second.y, other_second.z);
			glVertex3f(max.x, points[4], max.z);

			glVertex3f(other_third.x, other_third.y, other_third.z);
			glVertex3f(max.x, points[5], max.z);
			glEnd();
#endif
		}
		else if (vector.y != 0) {
			points.push_back(m_first.x + vector.x * (max.y - m_first.y));
			points.push_back(m_second.x + vector.x * (max.y - m_second.y));
			points.push_back(m_third.x + vector.x * (max.y - m_third.y));
			points.push_back(other_first.x + vector.x * (max.y - other_first.y));
			points.push_back(other_second.x + vector.x * (max.y - other_second.y));
			points.push_back(other_third.x + vector.x * (max.y - other_third.y));


#if 0
			glBegin(GL_LINES);
			glColor4f(0.0, 1.0, 0.0, 1.0);
			glVertex3f(MinFloat(points[0], points[1], points[2]), max.y, max.z);
			glVertex3f(MaxFloat(points[0], points[1], points[2]), max.y, max.z);

			glVertex3f(MinFloat(points[3], points[4], points[5]), max.y, max.z);
			glVertex3f(MaxFloat(points[3], points[4], points[5]), max.y, max.z);
			glEnd();

			glBegin(GL_LINES);
			glColor4f(0.0, 1.0, 0.0, 1.0);
			glVertex3f(m_first.x, m_first.y, m_first.z);
			glVertex3f(points[0], max.y, max.z);

			glVertex3f(m_second.x, m_second.y, m_second.z);
			glVertex3f(points[1], max.y, max.z);

			glVertex3f(m_third.x, m_third.y, m_third.z);
			glVertex3f(points[2], max.y, max.z);

			glVertex3f(other_first.x, other_first.y, other_first.z);
			glVertex3f(points[3], max.y, max.z);

			glVertex3f(other_second.x, other_second.y, other_second.z);
			glVertex3f(points[4], max.y, max.z);

			glVertex3f(other_third.x, other_third.y, other_third.z);
			glVertex3f(points[5], max.y, max.z);
			glEnd();

#endif
		}

		glm::vec2 firstSatLine(MinFloat(points[0], points[1], points[2]), MaxFloat(points[0], points[1], points[2]));
		glm::vec2 secondSatLine(MinFloat(points[3], points[4], points[5]), MaxFloat(points[3], points[4], points[5]));
		
		return LinesIntersect(firstSatLine, secondSatLine);;
	}

	bool Sat::LinesIntersect(const glm::vec2 &first, const glm::vec2 &second)
	{
		if (first.x > second.x && first.x < second.y ||
			first.y > second.x && first.y < second.y ||
			second.x > first.x && second.x < first.y ||
			second.y > first.x && second.y < first.y)	
			return true;
			return false;
	}

	glm::vec3 Sat::subFloat(const glm::vec3 &vector, float sub)
	{
		return glm::vec3(vector.x / sub, vector.y / sub, vector.z / sub);
	}

	glm::vec3 Sat::unitVec(const glm::vec3 &first, const glm::vec3 &second)
	{
		glm::vec3 result = first - second;
		float length = first.x - second.x;
		if (length != 0)
			return subFloat(result, length);

		//std::cout << "dsdsdasdsadasdas" << std::endl;
		length = first.y - second.y;
		if (length != 0)
			return subFloat(result, length);
	}

	glm::vec3 Sat::MaxValues(const glm::vec3 &first, const glm::vec3 &second, const glm::vec3 &third) const
	{
		glm::vec3 result;

		result.x = first.x;
		if (second.x > result.x) result.x = second.x;
		if (third.x > result.x) result.x = third.x;

		result.y = first.y;
		if (second.y > result.y) result.y = second.y;
		if (third.y > result.y) result.y = third.y;

		result.z = first.z;
		if (second.z > result.z) result.z = second.z;
		if (third.z > result.z) result.z = third.z;

		return result;
	}

	glm::vec3 Sat::MinValues(const glm::vec3 &first, const glm::vec3 &second, const glm::vec3 &third) const
	{
		glm::vec3 result;

		result.x = first.x;
		if (second.x < result.x) result.x = second.x;
		if (third.x < result.x) result.x = third.x;

		result.y = first.y;
		if (second.y < result.y) result.y = second.y;
		if (third.y < result.y) result.y = third.y;

		result.z = first.z;
		if (second.z < result.z) result.z = second.z;
		if (third.z < result.z) result.z = third.z;

		return result;
	}

	glm::vec3 Sat::MaxValues(const glm::vec3 &first, const glm::vec3 &second) const
	{
		glm::vec3 result;

		result.x = first.x;
		if (second.x > result.x) result.x = second.x;

		result.y = first.y;
		if (second.y > result.y) result.y = second.y;

		result.z = first.z;
		if (second.z > result.z) result.z = second.z;

		return result;
	}

	glm::vec3 Sat::MaxValues(const Sat &other) const
	{
		glm::vec3 result;
		result = lines[0].first;
		const Line *otherLines = other.getLines();
		for (unsigned int i = 0; i < other.getLineCount(); i++) {
			if (otherLines[i].first.x > result.x) result.x = otherLines[i].first.x;
			if (otherLines[i].first.y > result.y) result.y = otherLines[i].first.y;
			if (otherLines[i].first.z > result.z) result.z = otherLines[i].first.z;
			if (otherLines[i].second.x > result.x) result.x = otherLines[i].second.x;
			if (otherLines[i].second.y > result.y) result.y = otherLines[i].second.y;
			if (otherLines[i].second.z > result.z) result.z = otherLines[i].second.z;
		}
		for (unsigned int i = 0; i < this->getLineCount(); i++) {
			if (lines[i].first.x > result.x) result.x = lines[i].first.x;
			if (lines[i].first.y > result.y) result.y = lines[i].first.y;
			if (lines[i].first.z > result.z) result.z = lines[i].first.z;
			if (lines[i].second.x > result.x) result.x = lines[i].second.x;
			if (lines[i].second.y > result.y) result.y = lines[i].second.y;
			if (lines[i].second.z > result.z) result.z = lines[i].second.z;
		}
		return result;
	}

	glm::vec3 Sat::MinValues(const glm::vec3 &first, const glm::vec3 &second) const
	{
		glm::vec3 result;

		result.x = first.x;
		if (second.x < result.x) result.x = second.x;

		result.y = first.y;
		if (second.y < result.y) result.y = second.y;

		result.z = first.z;
		if (second.z < result.z) result.z = second.z;

		return result;
	}

	float Sat::MinFloat(float first, float second, float third)
	{
		float result = first;
		if (second < result) result = second;
		if (third < result) result = third;
		return result;
	}

	float Sat::MaxFloat(float first, float second, float third)
	{
		float result = first;
		if (second > result) result = second;
		if (third > result) result = third;
		return result;
	}

}