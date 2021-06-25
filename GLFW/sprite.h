#pragma once
#include "renderable2d.h"

namespace LM {

	class Sprite : public Renderable2D
	{
	private: 

	public:
		Sprite(float x, float y, float width, float height, const glm::vec4 &color);

		inline void addPosition(const glm::vec3 &vector) { m_Position += vector; }
		inline void setPosition(const glm::vec3 &position) { m_Position = position; }
		inline void setColor(const glm::vec4 &color) { m_Color = color; }

	};

}