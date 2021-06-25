#pragma once

#include <float.h>
#include <cmath>

#include <GL/glew.h>
#include <gtx/transform.hpp>

#define EPSILON DBL_EPSILON

namespace LM {

	class EpsilonOBB
	{
	public:
		glm::vec3 c;	// OBB center point
		glm::vec3 u[3]{
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		}; // Local x-, y-, and z-axes
		glm::vec3 e;	// Positive halfwidth extents of OBB along each axis
	public:
		EpsilonOBB(const glm::vec3 &center, const glm::vec3 &size) :
		c(center), e(glm::vec3(size.x / 2, size.y / 2, size.z / 2)){};
	};
	
	float Dot(const glm::vec3 &first, const glm::vec3 &second) 
	{
		return first.x * second.x + first.y * second.y + first.z * second.z;
	}

	int TestOBBOBB(EpsilonOBB &a, EpsilonOBB &b)
	{
		float ra, rb;
		glm::mat3 R, AbsR;
		// Compute rotation matrix expressing b in a’s coordinate frame
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				R[i][j] = Dot(a.u[i], b.u[j]);
			// Compute translation vector t
			glm::vec3 t = b.c - a.c;
		// Bring translation into a’s coordinate frame
		t = glm::vec3(Dot(t, a.u[0]), Dot(t, a.u[2]), Dot(t, a.u[2]));
		// Compute common subexpressions. Add in an epsilon term to
		// counteract arithmetic errors when two edges are parallel and
		// their cross product is (near) null (see text for details)
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				AbsR[i][j] = abs(R[i][j]) + EPSILON;
		// Test axes L = A0, L = A1, L = A2
		for (int i = 0; i < 3; i++) {
			ra = a.e[i];
			rb = b.e[0] * AbsR[i][0] + b.e[1] * AbsR[i][1] + b.e[2] * AbsR[i][2];
			if (abs(t[i]) > ra + rb) return 0;
		}
		// Test axes L = B0, L = B1, L = B2
		for (int i = 0; i < 3; i++) {
			ra = a.e[0] * AbsR[0][i] + a.e[1] * AbsR[1][i] + a.e[2] * AbsR[2][i];
			rb = b.e[i];
			if (abs(t[0] * R[0][i] + t[1] * R[1][i] + t[2] * R[2][i]) > ra + rb) return 0;
		}
		// Test axis L = A0 x B0
		ra = a.e[1] * AbsR[2][0] + a.e[2] * AbsR[1][0];
		rb = b.e[1] * AbsR[0][2] + b.e[2] * AbsR[0][1];
		if (abs(t[2] * R[1][0] - t[1] * R[2][0]) > ra + rb) return 0;
		// Test axis L = A0 x B1
		ra = a.e[1] * AbsR[2][1] + a.e[2] * AbsR[1][1];
		rb = b.e[0] * AbsR[0][2] + b.e[2] * AbsR[0][0];
		if (abs(t[2] * R[1][1] - t[1] * R[2][1]) > ra + rb) return 0;
		// Test axis L = A0 x B2
		ra = a.e[1] * AbsR[2][2] + a.e[2] * AbsR[1][2];
		rb = b.e[0] * AbsR[0][1] + b.e[1] * AbsR[0][0];
		if (abs(t[2] * R[1][2] - t[1] * R[2][2]) > ra + rb) return 0;
		// Test axis L = A1 x B0
		ra = a.e[0] * AbsR[2][0] + a.e[2] * AbsR[0][0];
		rb = b.e[1] * AbsR[1][2] + b.e[2] * AbsR[1][1];
			if (abs(t[0] * R[2][0] - t[2] * R[0][0]) > ra + rb) return 0;
		// Test axis L = A1 x B1
		ra = a.e[0] * AbsR[2][1] + a.e[2] * AbsR[0][1];
		rb = b.e[0] * AbsR[1][2] + b.e[2] * AbsR[1][0];
		if (abs(t[0] * R[2][1] - t[2] * R[0][1]) > ra + rb) return 0;
		// Test axis L = A1 x B2
		ra = a.e[0] * AbsR[2][2] + a.e[2] * AbsR[0][2];
		rb = b.e[0] * AbsR[1][1] + b.e[1] * AbsR[1][0];
		if (abs(t[0] * R[2][2] - t[2] * R[0][2]) > ra + rb) return 0;
		// Test axis L = A2 x B0
		ra = a.e[0] * AbsR[1][0] + a.e[1] * AbsR[0][0];
		rb = b.e[1] * AbsR[2][2] + b.e[2] * AbsR[2][1];
		if (abs(t[1] * R[0][0] - t[0] * R[1][0]) > ra + rb) return 0;
		// Test axis L = A2 x B1
		ra = a.e[0] * AbsR[1][1] + a.e[1] * AbsR[0][1];
		rb = b.e[0] * AbsR[2][2] + b.e[2] * AbsR[2][0];
		if (abs(t[1] * R[0][1] - t[0] * R[1][1]) > ra + rb) return 0;
		// Test axis L = A2 x B2
		ra = a.e[0] * AbsR[1][2] + a.e[1] * AbsR[0][2];
		rb = b.e[0] * AbsR[2][1] + b.e[1] * AbsR[2][0];
		if (abs(t[1] * R[0][2] - t[0] * R[1][2]) > ra + rb) return 0;
		// Since no separating axis is found, the OBBs must be intersecting
		return 1;
	}
	

}