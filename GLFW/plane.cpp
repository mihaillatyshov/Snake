#include "plane.h"
#include <cmath>

namespace LM {

	Plane Plane::Normolized() const {
		float magnitude = GetLength(m_Normal);

		return Plane(m_Normal / magnitude, m_Distance / magnitude);
	}

	IntersectData Plane::IntersectSphere(const BoundingSphere &other) const
	{
		float distanceFromSphereCenter = fabs(GetDot(m_Normal, other.getCenter()) + m_Distance);
		float distanceFromSphere = distanceFromSphereCenter - other.getRadius();

		return IntersectData(distanceFromSphere < 0, distanceFromSphere);
	}

	float Plane::GetLength(const glm::vec3 &vector) const
	{
		float result = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
		return result;
	}

	float Plane::GetDot(const glm::vec3 &first, const glm::vec3 &second) const
	{
		float result = 0.0f;
		result += first.x * second.x;
		result += first.y * second.y;
		result += first.z * second.z;

		return result;
	}

	/*
	inline float Dot(const glm::vec3 r) const
	{
		float result = 0.0f;
		result += this.x * r.x;
		result += this.y * r.y;
		result += this.z * r.z;

		return result
	}
	*/
}