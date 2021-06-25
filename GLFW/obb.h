#pragma once

#include <GL/glew.h>
#include <gtx/transform.hpp>

namespace LM {

	class OBB
	{
	private:
		glm::dvec4 pos[4];
		glm::dvec4 normal[2];
		glm::dvec4 normals[2];
		float m_width, m_height;
		glm::dmat4 m_transform;
		
		glm::vec3 position;
		glm::vec3 rotation;
	public:
		OBB(float width, float height, const glm::mat4 &transform);

		void draw() const;

		bool intersectOOB(const OBB &other);

		void addTransform(const glm::dmat4 &transform);
		void addTransform(const glm::vec4 &transform);
		void setTransform(const glm::dmat4 &transform);

	private:
		glm::vec3 MaxValues(const OBB &other);
		glm::vec2 MinMaxValues(const glm::vec4 &vector);
		glm::vec2 MinMaxValues(const glm::vec2 &vector);
		float CheckVectors(const glm::vec2 &first, const glm::vec2 &second);
		double CheckVectors(const glm::vec2 &first, const glm::vec2 &second, bool &side);
		unsigned char c(float f, float s, float t, float r);
	};

}