#pragma once

#include "boundingsphere.h"

namespace LM {

	class Plane
	{
	private:
		const glm::vec3 m_Normal;
		const float		m_Distance;
	public:
		Plane(const glm::vec3& normal, float distance) :
			m_Normal(normal),
			m_Distance(distance) {}

		Plane Normolized() const;
		IntersectData IntersectSphere(const BoundingSphere &other) const;

		inline const glm::vec3 GetNormal()	const { return m_Normal; }
		inline float GetDistance()			const { return m_Distance; }
	private:
		float GetLength(const glm::vec3 &vector) const;
		float GetDot(const glm::vec3 &first, const glm::vec3 &second) const;
	};

}