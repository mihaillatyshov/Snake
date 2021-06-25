#pragma once

#include <glm.hpp>
#include "intersectdata.h"
#include <iostream>
#include <vector>

namespace LM {

	struct Line 
	{
		const glm::vec3 &first;
		const glm::vec3 &second;
		const glm::vec3 &normal;

		Line (const glm::vec3 &Vfirst, const glm::vec3 &Vsecond, const glm::vec3 &Vnormal):
		first(Vfirst), second(Vsecond), normal(Vnormal) {}

		void addDisplacement(const glm::vec3 &displacement) 
		{
			*(const_cast<glm::vec3*>(&first)) += displacement;
			*(const_cast<glm::vec3*>(&second)) += displacement;
		}
	};

	class Sat
	{
	private:
		glm::vec3 m_first, m_second, m_third, m_velocity;

		std::vector<Line> lines;

		//Line m_firstLine, m_secondLine, m_thirdLine;

	public:
		Sat(const glm::vec3 &first, const glm::vec3 &second, const glm::vec3 &third) :
			m_first(first),
			m_second(second),
			m_third(third),
			m_velocity(glm::vec3(0.0f, 0.0f, 0.0f))
			/*m_firstLine(Line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
			m_secondLine(Line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f))),
			m_thirdLine(Line(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f))) */{}

		/*Sat(const Line &firstLine, const Line &secondLine, const Line &thirdLine) :
			m_firstLine(firstLine), 
			m_secondLine(secondLine), 
			m_thirdLine(thirdLine) {}*/
		
		Sat(Line *line, int lineNums)
		{
			std::cout << sizeof(*line) << " " << sizeof(lineNums) << std::endl;
			for (unsigned int i = 0; i < lineNums; i++)
				lines.push_back(line[i]);
			std::cout << lines[0].first.x << std::endl;
			lines[0].addDisplacement(glm::vec3(1, 0, 0));
			std::cout << lines[0].first.x << std::endl;
			std::cout << getLines()[0].first.x << std::endl;
		}

		IntersectData IntersectSAT(const Sat &other);

		inline glm::vec3 getFirstPoint() const { return m_first; }
		inline glm::vec3 getSecondPoint() const { return m_second; }
		inline glm::vec3 getThirdPoint() const { return m_third; }

		inline const Line *getLines() const { return &lines[0]; }
		inline int getLineCount() const { return lines.size(); }

		/*inline const Line &getFirstLine() const { return m_firstLine; }
		inline const Line &getSecondLine() const { return m_secondLine; }
		inline const Line &getThirdLine() const { return m_thirdLine; }*/

		inline void movePoints(const glm::vec3 &velocity) { m_first += velocity; m_second += velocity; m_third += velocity; m_velocity = velocity; }
	private:
		bool LinesIntersect(const glm::vec2 &first, const glm::vec2 &second);
		bool CheckVector(const glm::vec3 &unitVector, const Sat &other, const glm::vec3 &maxValues);
		glm::vec3 subFloat(const glm::vec3 &vector, float sub);
		glm::vec3 unitVec(const glm::vec3 &first, const glm::vec3 &second);

		glm::vec3 MaxValues(const glm::vec3 &first, const glm::vec3 &second, const glm::vec3 &third) const;
		glm::vec3 MaxValues(const Sat &other)														 const;
		glm::vec3 MinValues(const glm::vec3 &first, const glm::vec3 &second, const glm::vec3 &third) const;
		glm::vec3 MaxValues(const glm::vec3 &first, const glm::vec3 &second)						 const;
		glm::vec3 MinValues(const glm::vec3 &first, const glm::vec3 &second)						 const;

		float MinFloat(float first, float second, float third);
		float MaxFloat(float first, float second, float third);
	};

}