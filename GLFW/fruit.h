#pragma once

#include <glm.hpp>
#include "sprite.h"
#include <ctime>

namespace LM {

	class Fruit
	{
	public:
		Fruit();
		glm::ivec2 m_position;
		Sprite m_sprite;
		void setNewPosition(const glm::ivec2 &maxPos);
	};

}