#pragma once

namespace LM {

	class IntersectData
	{
	private:
		const bool m_DoesIntersect;
		const float m_Distance;
	public:
		IntersectData(const bool DoesIntersect, const float distance) :
			m_DoesIntersect(DoesIntersect),
			m_Distance(distance) {}

		inline bool GetDoesIntersect()	const { return m_DoesIntersect; }
		inline float GetDistance()		const { return m_Distance; }
	};

}