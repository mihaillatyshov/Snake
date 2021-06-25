#pragma once

#include "timer.h"
#include <GL/glew.h>
#include <gtx/transform.hpp>

namespace LM {

	class OBB_2
	{
	private:
		glm::dvec4 m_pos[4];
		glm::dvec4 m_normals[2];


		glm::dvec3 m_location;
		glm::dvec3 m_rotation;

	public:
		OBB_2(const glm::dvec2 &size, const glm::dvec3 &location, const glm::dvec3 rotation);

		bool intersectOOB(const OBB_2 &other);
		void draw() const;

		inline void setLocation(const glm::dvec3 &location) { m_location = location; }
		inline void addLocation(const glm::dvec3 &vector) { m_location += vector; }
		inline void simulate() { m_location -= glm::dvec3(0.0 * LM::Timer::lastFrame, 1 * LM::Timer::lastFrame, 0.0 * LM::Timer::lastFrame); }

	private:
		glm::dvec3 MaxValues(const OBB_2 &other);
		unsigned char c(double f, double s, double t, double r);
		double CheckVectors(const glm::dvec2 &first, const glm::dvec2 &second, bool &side);
		glm::dvec2 MinMaxValues(const glm::dvec4 &vector);
		glm::dvec2 MinMaxValues(const glm::dvec2 &vector);
	};

}