#include "obbnew.h"

#include <iostream>

#define MY_PI            3.14159265358979323846

namespace LM {

	OBB_2::OBB_2(const glm::dvec2 &size, const glm::dvec3 &location, const glm::dvec3 rotation) :
		m_rotation(rotation), m_location(location)
	{
		m_pos[0] = (glm::dvec4(-size.x / 2, -size.y / 2, 0, 1));
		m_pos[1] = (glm::dvec4(size.x / 2, -size.y / 2, 0, 1));
		m_pos[2] = (glm::dvec4(size.x / 2, size.y / 2, 0, 1));
		m_pos[3] = (glm::dvec4(-size.x / 2, size.y / 2, 0, 1));

		m_normals[0] = glm::dvec4(1, 0, 0, 0);
		m_normals[1] = glm::dvec4(0, 1, 0, 0);
	}

	bool OBB_2::intersectOOB(const OBB_2 &other)
	{

		glm::dmat4 transform = glm::translate(m_location) * glm::rotate(m_rotation.x / 180.0 * MY_PI, glm::dvec3(0, 0, 1));

		glm::dvec4 pos[4];
		glm::dvec4 normals[2];
		pos[0] = transform * m_pos[0];
		pos[1] = transform * m_pos[1];
		pos[2] = transform * m_pos[2];
		pos[3] = transform * m_pos[3];

		normals[0] = transform * m_normals[0];
		normals[1] = transform * m_normals[1];



		transform = glm::translate(other.m_location) * glm::rotate(other.m_rotation.x / 180.0 * MY_PI, glm::dvec3(0, 0, 1));

		glm::dvec4 otherpos[4];
		glm::dvec4 othernormals[2];
		otherpos[0] = transform * other.m_pos[0];
		otherpos[1] = transform * other.m_pos[1];
		otherpos[2] = transform * other.m_pos[2];
		otherpos[3] = transform * other.m_pos[3];

		othernormals[0] = transform * other.m_normals[0];
		othernormals[1] = transform * other.m_normals[1];



		glm::dvec3 maxValues = MaxValues(other);

		double detectionSize[4];
		bool side[4];



		glm::dvec3 test1(normals[0].x / normals[0].x, normals[0].y / normals[0].x, 0); // 0 , 2 

		  //float firtst = pos[0].y + (maxValues.x - pos[0].x) * test1.y;
																					  //float second = pos[2].y + (maxValues.x - pos[2].x) * test1.y;

		glm::dvec2 first(pos[0].y + (maxValues.x - pos[0].x) * test1.y,
			pos[2].y + (maxValues.x - pos[2].x) * test1.y);

		glm::dvec4 second(otherpos[0].y + (maxValues.x - otherpos[0].x) * test1.y,
			otherpos[1].y + (maxValues.x - otherpos[1].x) * test1.y,
			otherpos[2].y + (maxValues.x - otherpos[2].x) * test1.y,
			otherpos[3].y + (maxValues.x - otherpos[3].x) * test1.y);

		glm::dvec2 f = MinMaxValues(first);
		glm::dvec2 s = MinMaxValues(second);

		detectionSize[0] = CheckVectors(f, s, side[0]);
		std::cout << CheckVectors(f, s, side[0]) << std::endl;



		glm::dvec3 test2(normals[1].x / normals[1].x, normals[1].y / normals[1].x, 0);

		first = glm::dvec2(pos[0].y + (maxValues.x - pos[0].x) * test2.y,
			pos[2].y + (maxValues.x - pos[2].x) * test2.y);

		second = glm::dvec4(otherpos[0].y + (maxValues.x - otherpos[0].x) * test2.y,
			otherpos[1].y + (maxValues.x - otherpos[1].x) * test2.y,
			otherpos[2].y + (maxValues.x - otherpos[2].x) * test2.y,
			otherpos[3].y + (maxValues.x - otherpos[3].x) * test2.y);

		f = MinMaxValues(first);
		s = MinMaxValues(second);

		detectionSize[1] = CheckVectors(f, s, side[1]);
		std::cout << CheckVectors(f, s, side[1]) << std::endl;



		glm::dvec3 test3(othernormals[0].x / othernormals[0].x, othernormals[0].y / othernormals[0].x, 0);

		first = glm::dvec2(otherpos[0].y + (maxValues.x - otherpos[0].x) * test3.y,
			otherpos[2].y + (maxValues.x - otherpos[2].x) * test3.y);

		second = glm::dvec4(pos[0].y + (maxValues.x - pos[0].x) * test3.y,
			pos[1].y + (maxValues.x - pos[1].x) * test3.y,
			pos[2].y + (maxValues.x - pos[2].x) * test3.y,
			pos[3].y + (maxValues.x - pos[3].x) * test3.y);

		f = MinMaxValues(first);
		s = MinMaxValues(second);

		detectionSize[2] = CheckVectors(f, s, side[2]);
		std::cout << CheckVectors(f, s, side[2]) << std::endl;





		glm::dvec3 test4(othernormals[1].x / othernormals[1].x, othernormals[1].y / othernormals[1].x, 0);

		first = glm::dvec2(otherpos[0].y + (maxValues.x - otherpos[0].x) * test4.y,
			otherpos[2].y + (maxValues.x - otherpos[2].x) * test4.y);

		second = glm::dvec4(pos[0].y + (maxValues.x - pos[0].x) * test4.y,
			pos[1].y + (maxValues.x - pos[1].x) * test4.y,
			pos[2].y + (maxValues.x - pos[2].x) * test4.y,
			pos[3].y + (maxValues.x - pos[3].x) * test4.y);

		f = MinMaxValues(first);
		s = MinMaxValues(second);

		detectionSize[3] = CheckVectors(f, s, side[3]);
		std::cout << CheckVectors(f, s, side[3]) << std::endl;



		for (unsigned short i = 0; i < 4; i++)
			if (detectionSize[i] < 0) {
				return false;
			}

		glm::dvec4 normalMove;

		switch (int(c(detectionSize[0], detectionSize[1], detectionSize[2], detectionSize[3]))) {
		case 0:
			if (side[0])
				normalMove = normals[1];
			else
				normalMove = glm::dvec4(normals[1].x * -1, normals[1].y * -1, normals[1].z * -1, normals[1].w);
			(const_cast<LM::OBB_2*>(&other))->addLocation(glm::dvec3(normalMove.x * abs(normalMove.x) * detectionSize[0],
				normalMove.y * abs(normalMove.y) * detectionSize[0], 0));
			break;
		case 1:
			if (side[1])
				normalMove = normals[0];
			else
				normalMove = glm::dvec4(normals[0].x * -1, normals[0].y * -1, normals[0].z * -1, normals[0].w);
			(const_cast<LM::OBB_2*>(&other))->addLocation(glm::dvec3(normalMove.x * abs(normalMove.x) * detectionSize[1],
				normalMove.y * abs(normalMove.y) * detectionSize[1], 0));
			break;
		case 2:
			if (side[2])
				normalMove = glm::dvec4(othernormals[1].x * -1, othernormals[1].y * -1, othernormals[1].z * -1, othernormals[1].w);
			else
				normalMove = othernormals[1];
			(const_cast<LM::OBB_2*>(&other))->addLocation(glm::dvec3(normalMove.x * abs(normalMove.x) * detectionSize[2],
				normalMove.y * abs(normalMove.y) * detectionSize[2], 0));
			break;
		case 3:
			if (side[3])
				normalMove = glm::dvec4(othernormals[0].x * -1, othernormals[0].y * -1, othernormals[0].z * -1, othernormals[0].w);
			else
				normalMove = othernormals[0];
			(const_cast<LM::OBB_2*>(&other))->addLocation(glm::dvec3(normalMove.x * abs(normalMove.x) * detectionSize[3],
				normalMove.y * abs(normalMove.y) * detectionSize[3], 0));
			break;
		}


		return true;
	}

	void OBB_2::draw() const
	{
		glm::dmat4 transform = glm::translate(m_location) * glm::rotate(m_rotation.x / 180.0 * MY_PI, glm::dvec3(0, 0, 1));

		glm::dvec4 pos[4];
		pos[0] = transform * m_pos[0];
		pos[1] = transform * m_pos[1];
		pos[2] = transform * m_pos[2];
		pos[3] = transform * m_pos[3];


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

		/*glVertex3f(1, 1, 0);
		glVertex3f(1 + normals[1].x, 1 + normals[1].y, 0);*/

		glEnd();
	}

	glm::dvec2 OBB_2::MinMaxValues(const glm::dvec4 &vector)
	{
		glm::dvec2 result(vector.x, vector.x);
		if (result.x > vector.y) result.x = vector.y;
		if (result.x > vector.z) result.x = vector.z;
		if (result.x > vector.w) result.x = vector.w;

		if (result.y < vector.y) result.y = vector.y;
		if (result.y < vector.z) result.y = vector.z;
		if (result.y < vector.w) result.y = vector.w;

		return result;
	}

	glm::dvec2 OBB_2::MinMaxValues(const glm::dvec2 &vector)
	{
		glm::dvec2 result(vector.x, vector.x);
		if (result.x > vector.y) result.x = vector.y;

		if (result.y < vector.y) result.y = vector.y;

		return result;
	}

	double OBB_2::CheckVectors(const glm::dvec2 &first, const glm::dvec2 &second, bool &side)
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

	unsigned char OBB_2::c(double f, double s, double t, double r)
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

	glm::dvec3 OBB_2::MaxValues(const OBB_2 &other)
	{
		glm::dmat4 transform = glm::translate(m_location) * glm::rotate(m_rotation.x / 180.0 * MY_PI, glm::dvec3(0, 0, 1));

		glm::dvec4 pos[4];
		pos[0] = transform * m_pos[0];
		pos[1] = transform * m_pos[1];
		pos[2] = transform * m_pos[2];
		pos[3] = transform * m_pos[3];



		glm::dvec3 result(pos[0].x, pos[0].y, pos[0].z);
		for (unsigned short i = 1; i < 4; i++) {
			if (result.x < pos[i].x) result.x = pos[i].x;
			if (result.y < pos[i].y) result.y = pos[i].y;
		}

		transform = glm::translate(other.m_location) * glm::rotate(other.m_rotation.x / 180.0 * MY_PI, glm::dvec3(0, 0, 1));

		pos[0] = transform * other.m_pos[0];
		pos[1] = transform * other.m_pos[1];
		pos[2] = transform * other.m_pos[2];
		pos[3] = transform * other.m_pos[3];

		for (unsigned short i = 0; i < 4; i++) {
			if (result.x < pos[i].x) result.x = pos[i].x;
			if (result.y < pos[i].y) result.y = pos[i].y;
		}
		return result;
	}

}