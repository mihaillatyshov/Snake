#include "obb.h"
#include <iostream>
#include <cmath>

namespace LM {

	OBB::OBB(float width, float height, const glm::mat4 &transform) :
		m_width(width), m_height(height),
		m_transform(transform)
	{
		pos[0] = m_transform * glm::vec4(-m_width / 2, -m_height / 2, 0, 1);
		pos[1] = m_transform * glm::vec4(m_width / 2, -m_height / 2, 0, 1);
		pos[2] = m_transform * glm::vec4(m_width / 2, m_height / 2, 0, 1);
		pos[3] = m_transform * glm::vec4(-m_width / 2, m_height / 2, 0, 1);

		normals[0] = m_transform * glm::dvec4(1, 0, 0, 0);
		normals[1] = m_transform * glm::dvec4(0, 1, 0, 0);

	}

	void OBB::draw() const {

		glBegin(GL_LINES);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		// -normal1
		glVertex3f(pos[0].x, pos[0].y, 0);
		glVertex3f(pos[1].x, pos[1].y, 0);

		// normal0
		glVertex3f(pos[1].x, pos[1].y, 0);
		glVertex3f(pos[2].x, pos[2].y, 0);

		// normal1
		glVertex3f(pos[2].x, pos[2].y, 0);
		glVertex3f(pos[3].x, pos[3].y, 0);

		// -normal0
		glVertex3f(pos[3].x, pos[3].y, 0);
		glVertex3f(pos[0].x, pos[0].y, 0);

		glVertex3f(1, 1, 0);
		glVertex3f(1 + normals[1].x, 1 + normals[1].y, 0);

		glEnd();

		//std::cout << normals[1].x << " " << normals[1].y << std::endl;

	}

	bool OBB::intersectOOB(const OBB &other)
	{

		glm::vec3 maxValues = MaxValues(other);

		double detectionSize[4];
		bool side[4];

		glm::vec3 test1(normals[0].x / normals[0].x, normals[0].y / normals[0].x, 0); // 0 , 2 

		//float firtst = pos[0].y + (maxValues.x - pos[0].x) * test1.y;
		//float second = pos[2].y + (maxValues.x - pos[2].x) * test1.y;

		glm::vec2 first(pos[0].y + (maxValues.x - pos[0].x) * test1.y,
						pos[2].y + (maxValues.x - pos[2].x) * test1.y);

		glm::vec4 second(other.pos[0].y + (maxValues.x - other.pos[0].x) * test1.y,
						 other.pos[1].y + (maxValues.x - other.pos[1].x) * test1.y,
						 other.pos[2].y + (maxValues.x - other.pos[2].x) * test1.y,
						 other.pos[3].y + (maxValues.x - other.pos[3].x) * test1.y);
		

		glm::vec2 f = MinMaxValues(first);
		glm::vec2 s = MinMaxValues(second);

		detectionSize[0] = CheckVectors(f, s, side[0]);
		std::cout << CheckVectors(f, s, side[0]) << std::endl;

#if 1
		glBegin(GL_LINES);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glVertex3f(pos[0].x, pos[0].y, 0);
		glVertex3f(maxValues.x, first.x, 0);

		glVertex3f(pos[2].x, pos[2].y, 0);
		glVertex3f(maxValues.x, first.y, 0);

		glVertex3f(other.pos[0].x, other.pos[0].y, 0);
		glVertex3f(maxValues.x, second.x, 0);

		glVertex3f(other.pos[1].x, other.pos[1].y, 0);
		glVertex3f(maxValues.x, second.y, 0);

		glVertex3f(other.pos[2].x, other.pos[2].y, 0);
		glVertex3f(maxValues.x, second.z, 0);

		glVertex3f(other.pos[3].x, other.pos[3].y, 0);
		glVertex3f(maxValues.x, second.w, 0);

		glVertex3f(maxValues.x + 2, f.x, 0);
		glVertex3f(maxValues.x + 2, f.y, 0);

		glVertex3f(maxValues.x + 1.5, s.x, 0);
		glVertex3f(maxValues.x + 1.5, s.y, 0);

		glEnd();
#endif

		//std::cout << firtst << " " << second << std::endl;

		glm::vec3 test2(normals[1].x / normals[1].x, normals[1].y / normals[1].x, 0);

		first = glm::vec2(pos[0].y + (maxValues.x - pos[0].x) * test2.y,
						  pos[2].y + (maxValues.x - pos[2].x) * test2.y);

		second = glm::vec4(other.pos[0].y + (maxValues.x - other.pos[0].x) * test2.y,
						   other.pos[1].y + (maxValues.x - other.pos[1].x) * test2.y,
						   other.pos[2].y + (maxValues.x - other.pos[2].x) * test2.y,
						   other.pos[3].y + (maxValues.x - other.pos[3].x) * test2.y);

		f = MinMaxValues(first);
		s = MinMaxValues(second);

		detectionSize[1] = CheckVectors(f, s, side[1]);
		std::cout << CheckVectors(f, s, side[1]) << std::endl;

		//std::cout << side[0] << " " << side[1] << std::endl;
#if 1
		glBegin(GL_LINES);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glVertex3f(pos[0].x, pos[0].y, 0);
		glVertex3f(maxValues.x, first.x, 0);

		glVertex3f(pos[2].x, pos[2].y, 0);
		glVertex3f(maxValues.x, first.y, 0);

		glVertex3f(other.pos[0].x, other.pos[0].y, 0);
		glVertex3f(maxValues.x, second.x, 0);

		glVertex3f(other.pos[1].x, other.pos[1].y, 0);
		glVertex3f(maxValues.x, second.y, 0);

		glVertex3f(other.pos[2].x, other.pos[2].y, 0);
		glVertex3f(maxValues.x, second.z, 0);

		glVertex3f(other.pos[3].x, other.pos[3].y, 0);
		glVertex3f(maxValues.x, second.w, 0);

		glVertex3f(maxValues.x + 1, f.x, 0);
		glVertex3f(maxValues.x + 1, f.y, 0);

		glVertex3f(maxValues.x + 0.5, s.x, 0);
		glVertex3f(maxValues.x + 0.5, s.y, 0);

		glEnd();
#endif


		glm::vec3 test3(other.normals[0].x / other.normals[0].x, other.normals[0].y / other.normals[0].x, 0);

		first = glm::vec2(other.pos[0].y + (maxValues.x - other.pos[0].x) * test3.y,
						  other.pos[2].y + (maxValues.x - other.pos[2].x) * test3.y);

		second = glm::vec4(pos[0].y + (maxValues.x - pos[0].x) * test3.y,
						   pos[1].y + (maxValues.x - pos[1].x) * test3.y,
						   pos[2].y + (maxValues.x - pos[2].x) * test3.y,
						   pos[3].y + (maxValues.x - pos[3].x) * test3.y);

		f = MinMaxValues(first);
		s = MinMaxValues(second);

		detectionSize[2] = CheckVectors(f, s, side[2]);
		std::cout << CheckVectors(f, s, side[2]) << std::endl;

#if 0
		glBegin(GL_LINES);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glVertex3f(other.pos[0].x, other.pos[0].y, 0);
		glVertex3f(maxValues.x, first.x, 0);

		glVertex3f(other.pos[2].x, other.pos[2].y, 0);
		glVertex3f(maxValues.x, first.y, 0);

		glVertex3f(pos[0].x, pos[0].y, 0);
		glVertex3f(maxValues.x, second.x, 0);

		glVertex3f(pos[1].x, pos[1].y, 0);
		glVertex3f(maxValues.x, second.y, 0);

		glVertex3f(pos[2].x, pos[2].y, 0);
		glVertex3f(maxValues.x, second.z, 0);

		glVertex3f(pos[3].x, pos[3].y, 0);
		glVertex3f(maxValues.x, second.w, 0);

		glVertex3f(maxValues.x + 1, f.x, 0);
		glVertex3f(maxValues.x + 1, f.y, 0);

		glVertex3f(maxValues.x + 0.5, s.x, 0);
		glVertex3f(maxValues.x + 0.5, s.y, 0);

		glEnd();
#endif

		glm::vec3 test4(other.normals[1].x / other.normals[1].x, other.normals[1].y / other.normals[1].x, 0);

		first = glm::vec2(other.pos[0].y + (maxValues.x - other.pos[0].x) * test4.y,
						  other.pos[2].y + (maxValues.x - other.pos[2].x) * test4.y);

		second = glm::vec4(pos[0].y + (maxValues.x - pos[0].x) * test4.y,
						   pos[1].y + (maxValues.x - pos[1].x) * test4.y,
						   pos[2].y + (maxValues.x - pos[2].x) * test4.y,
						   pos[3].y + (maxValues.x - pos[3].x) * test4.y);

		f = MinMaxValues(first);
		s = MinMaxValues(second);

		detectionSize[3] = CheckVectors(f, s, side[3]);
		std::cout << CheckVectors(f, s, side[3]) << std::endl;

#if 0
		glBegin(GL_LINES);
		glColor4f(0.0, 0.0, 1.0, 1.0);
		glVertex3f(other.pos[0].x, other.pos[0].y, 0);
		glVertex3f(maxValues.x, first.x, 0);

		glVertex3f(other.pos[2].x, other.pos[2].y, 0);
		glVertex3f(maxValues.x, first.y, 0);

		glVertex3f(pos[0].x, pos[0].y, 0);
		glVertex3f(maxValues.x, second.x, 0);

		glVertex3f(pos[1].x, pos[1].y, 0);
		glVertex3f(maxValues.x, second.y, 0);

		glVertex3f(pos[2].x, pos[2].y, 0);
		glVertex3f(maxValues.x, second.z, 0);

		glVertex3f(pos[3].x, pos[3].y, 0);
		glVertex3f(maxValues.x, second.w, 0);

		glVertex3f(maxValues.x + 1, f.x, 0);
		glVertex3f(maxValues.x + 1, f.y, 0);

		glVertex3f(maxValues.x + 0.5, s.x, 0);
		glVertex3f(maxValues.x + 0.5, s.y, 0);

		glEnd();
#endif

		for (unsigned short i = 0; i < 4; i++)
			if (detectionSize[i] < 0) {
				other.draw();
				draw();
				return false;
			}

		glm::dvec4 normalMove;


		switch (int(c(detectionSize[0], detectionSize[1], detectionSize[2], detectionSize[3]))) {
		case 0:
			if (side[0])
				normalMove = normals[1];
			else
				normalMove = glm::dvec4(normals[1].x * -1, normals[1].y * -1, normals[1].z * -1, normals[1].w);
			(const_cast<LM::OBB*>(&other))->addTransform(glm::translate(glm::dvec3(normalMove.x * abs(normalMove.x) * detectionSize[0],
																				  normalMove.y * abs(normalMove.y) * detectionSize[0], 0)));
			break;
		case 1:
			if (side[1])
				normalMove = normals[0];
			else
				normalMove = glm::dvec4(normals[0].x * -1, normals[0].y * -1, normals[0].z * -1, normals[0].w);
			(const_cast<LM::OBB*>(&other))->addTransform(glm::translate(glm::dvec3(normalMove.x * abs(normalMove.x) * detectionSize[1],
																				  normalMove.y * abs(normalMove.y) * detectionSize[1], 0)));
			break;
		case 2:
			if (side[2])
				normalMove = glm::dvec4(other.normals[1].x * -1, other.normals[1].y * -1, other.normals[1].z * -1, other.normals[1].w);
			else
				normalMove = other.normals[1];
			(const_cast<LM::OBB*>(&other))->addTransform(glm::translate(glm::dvec3(normalMove.x * abs(normalMove.x) * detectionSize[2],
																				  normalMove.y * abs(normalMove.y) * detectionSize[2], 0)));

			/*(const_cast<LM::OBB*>(&other))->addTransform(glm::dvec4(normalMove.y * fabs(normalMove.y) * detectionSize[2],
																   normalMove.x * fabs(normalMove.x) * detectionSize[2], 0, 0));*/
			break;
		case 3:
			if (side[3])
				normalMove = glm::dvec4(other.normals[0].x * -1, other.normals[0].y * -1, other.normals[0].z * -1, other.normals[0].w);
			else
				normalMove = other.normals[0];
			(const_cast<LM::OBB*>(&other))->addTransform(glm::translate(glm::dvec3(normalMove.x * abs(normalMove.x) * detectionSize[3],
																				  normalMove.y * abs(normalMove.y) * detectionSize[3], 0)));

			/*(const_cast<LM::OBB*>(&other))->addTransform(glm::dvec4(normalMove.y * fabs(normalMove.y) * detectionSize[3],
																   normalMove.x * fabs(normalMove.x) * detectionSize[3], 0, 0));*/
			break;
		}

		/*
		if (detectionSize[0] < detectionSize[1]) {
			if (side[0])
				normalMove = normals[1];
			else
				normalMove = glm::vec4(normals[1].x * -1, normals[1].y * -1, normals[1].z * -1, normals[1].w);
			(const_cast<LM::OBB*>(&other))->addTransform(glm::translate(glm::vec3(normalMove.x * abs(normalMove.x) * detectionSize[0],
																				  normalMove.y * abs(normalMove.y) * detectionSize[0], 0)));
			
		}
		else {
			if (side[1])
				normalMove = normals[0];
			else
				normalMove = glm::vec4(normals[0].x * -1, normals[0].y * -1, normals[0].z * -1, normals[0].w);
			(const_cast<LM::OBB*>(&other))->addTransform(glm::translate(glm::vec3(normalMove.x * abs(normalMove.x) * detectionSize[1],
																				  normalMove.y * abs(normalMove.y) * detectionSize[1], 0)));
		}*/

		other.draw();
		draw();

		return true;
	}

	glm::vec3 OBB::MaxValues(const OBB &other)
	{
		glm::vec3 result(pos[0].x, pos[0].y, pos[0].z);
		for (unsigned short i = 1; i < 4; i++) {
			if (result.x < pos[i].x) result.x = pos[i].x;
			if (result.y < pos[i].y) result.y = pos[i].y;
		}
		for (unsigned short i = 0; i < 4; i++) {
			if (result.x < other.pos[i].x) result.x = other.pos[i].x;
			if (result.y < other.pos[i].y) result.y = other.pos[i].y;
		}
		return result;
	}

	glm::vec2 OBB::MinMaxValues(const glm::vec4 &vector)
	{
		glm::vec2 result(vector.x, vector.x);
		if (result.x > vector.y) result.x = vector.y;
		if (result.x > vector.z) result.x = vector.z;
		if (result.x > vector.w) result.x = vector.w;

		if (result.y < vector.y) result.y = vector.y;
		if (result.y < vector.z) result.y = vector.z;
		if (result.y < vector.w) result.y = vector.w;

		return result;
	}

	glm::vec2 OBB::MinMaxValues(const glm::vec2 &vector)
	{
		glm::vec2 result(vector.x, vector.x);
		if (result.x > vector.y) result.x = vector.y;

		if (result.y < vector.y) result.y = vector.y;

		return result;
	}

	float OBB::CheckVectors(const glm::vec2 &first, const glm::vec2 &second)
	{
		if (first.y < second.x || second.y < first.x)
			return -1.0f;
		else return first.y - second.x < second.y - first.x ? first.y - second.x : second.y - first.x;
	}

	double OBB::CheckVectors(const glm::vec2 &first, const glm::vec2 &second, bool &side)
	{
		if (first.y < second.x || second.y < first.x) {
			side = false;
			return -1.0f;
		}
		else {
			if (first.y - second.x < second.y - first.x) {
				side = true;
				return first.y - second.x;
			}
			else {
				side = false;
				return second.y - first.x;
			}
		}
	}

	void OBB::addTransform(const glm::dmat4 &transform) 
	{
		m_transform = transform * m_transform;
		//m_transform *= transform;
		pos[0] = m_transform * glm::vec4(-m_width / 2, -m_height / 2, 0, 1);
		pos[1] = m_transform * glm::vec4(m_width / 2, -m_height / 2, 0, 1);
		pos[2] = m_transform * glm::vec4(m_width / 2, m_height / 2, 0, 1);
		pos[3] = m_transform * glm::vec4(-m_width / 2, m_height / 2, 0, 1);

		normals[0] = m_transform * glm::dvec4(1, 0, 0, 0);
		normals[1] = m_transform * glm::dvec4(0, 1, 0, 0);
	}

	void OBB::addTransform(const glm::vec4 &transform)
	{
		pos[0] += transform;
		pos[1] += transform;
		pos[2] += transform;
		pos[3] += transform;

	}

	void OBB::setTransform(const glm::dmat4 &transform) 
	{
		m_transform = transform;
		pos[0] = m_transform * glm::vec4(-m_width / 2, -m_height / 2, 0, 1);
		pos[1] = m_transform * glm::vec4(m_width / 2, -m_height / 2, 0, 1);
		pos[2] = m_transform * glm::vec4(m_width / 2, m_height / 2, 0, 1);
		pos[3] = m_transform * glm::vec4(-m_width / 2, m_height / 2, 0, 1);

		normals[0] = m_transform * glm::dvec4(1, 0, 0, 0);
		normals[1] = m_transform * glm::dvec4(0, 1, 0, 0);
	}

	unsigned char OBB::c(float f, float s, float t, float r)
	{
		unsigned char result = 0;
		if (f < s && f < t && f < r)
			result = 0;
		else if (s<f && s<t && s<r)
			result = 1;
		else if (t<f && t<s && t<r)
			result = 2;
		else if (r<f && r<s && r<t)
			result = 3;

		return result;
	}

}