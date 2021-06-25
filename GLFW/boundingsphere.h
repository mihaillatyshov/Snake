#pragma once

#include <glm.hpp>
#include "intersectdata.h"

namespace LM {

	class BoundingSphere
	{
	private:
		const glm::vec3	m_Center;
		const float		m_Radius;
	public:
		BoundingSphere(const glm::vec3 &center, float radius) :
			m_Center(center),
			m_Radius(radius){}

		IntersectData IntersectBoundingSphere(const BoundingSphere &other);

		inline const glm::vec3 getCenter()	const { return m_Center; }
		inline float getRadius()			const { return m_Radius; }
	private:
		float GetLength(const glm::vec3 &first, const glm::vec3 &second);

	};

}