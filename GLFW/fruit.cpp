#include "fruit.h"

namespace LM {

	Fruit::Fruit() :
		m_position(glm::ivec2(4, 5)),
		m_sprite(Sprite(m_position.x + 0.05f, m_position.y + 0.05f, 0.9f, 0.9f, glm::vec4(0, 1, 0, 1)))
	{
	}
	void Fruit::setNewPosition(const glm::ivec2 &maxPos) {
		m_position = glm::ivec2(rand() % (maxPos.x -2) + 1, rand() % (maxPos.y - 2) + 1);
		m_sprite.setPosition(glm::vec3(m_position.x + 0.05f, m_position.y + 0.05f, 0));
	}

}