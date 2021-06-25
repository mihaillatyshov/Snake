#include "boundingsphere.h"

#include <iostream>
#include <cmath>

namespace LM {

	IntersectData BoundingSphere::IntersectBoundingSphere(const BoundingSphere &other) {
		float radiusDistance = m_Radius + other.m_Radius;
		float centerDistance = GetLength(other.getCenter(), m_Center);
		std::cout << centerDistance << std::endl;
		float distance = centerDistance - radiusDistance;

		return IntersectData(centerDistance < radiusDistance, distance);
	}

	float BoundingSphere::GetLength(const glm::vec3 &first, const glm::vec3 &second) {
		float result = sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2) + pow(second.z - first.z, 2));
		return result;
	}
}