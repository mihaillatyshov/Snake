#include "aabb.h"

namespace LM {

	IntersectData AABB::IntersectAABB(const AABB &other) const 
	{
		glm::vec3 distances1 = other.GetMinExtents() - m_MaxExtents;
		glm::vec3 distances2 = m_MinExtents - other.GetMaxExtents();
		glm::vec3 distances = Max(distances1, distances2);

		float maxDistance = MaxVal(distances);

		return IntersectData(maxDistance < 0, maxDistance);
	}


	float AABB::MaxVal(const glm::vec3 &vector) const
	{
		float maxVal = vector.x;

		if (vector.y > maxVal) maxVal = vector.y;
		if (vector.z > maxVal) maxVal = vector.z;

		return maxVal;
	}

	const glm::vec3 &AABB::Max(const glm::vec3 &first, const glm::vec3 &second) const
	{
		glm::vec3 result = glm::vec3(
			first.x > second.x ? first.x : second.x,
			first.y > second.y ? first.y : second.y,
			first.z > second.z ? first.z : second.z
		);

		return result;
	}

}