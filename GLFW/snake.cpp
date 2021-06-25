
#include <GL/glew.h>
#include <glfw3.h>

#include "snake.h"
#include "timer.h"


namespace LM {

	Snake::Snake(const glm::ivec2 &position, const glm::ivec2 &maxPos) :
		m_Head(position), m_MaxPos(maxPos) {
		m_Head.m_sprite.setColor(glm::vec4(0.6, 0, 0.2, 1));
	}

	bool Snake::update(Fruit* fruit)
	{
		if (m_SnakeTime >= 0.2f) {
			glm::ivec2 move(0, 0);
			if (m_Direction == EDirection::UP) {			if (m_Head.m_position.y != m_MaxPos.y - 2)	move = glm::vec3(0, 1, 0); }
			else if (m_Direction == EDirection::DOWN) {	if (m_Head.m_position.y != 1)				move = glm::vec3(0, -1, 0); }
			else if (m_Direction == EDirection::RIGHT) {	if (m_Head.m_position.x != m_MaxPos.x - 2)	move = glm::vec3(1, 0, 0); }
			else {							if (m_Head.m_position.x != 1)				move = glm::vec3(-1, 0, 0); }
			
			m_LastDirection = m_Direction;

			if (move.x != 0 || move.y != 0) {
				m_Head.addPosition(move);
				if (m_Head.m_position == fruit->m_position) {
					fruit->setNewPosition(m_MaxPos);
					if (GetTailLength() == 0) {
						m_Tail.push_back(Section(m_Head.m_position));
					}
					else
					{
						m_Tail.push_back(Section(m_Tail[GetTailLength() - 1].m_position));
					}
				}

				UpdateTail(move);
				if (CheckCollision()) {
					return false;
				}
			}
			else {
				return false;
			}

			m_SnakeTime = 0;
		}
		else {
			m_SnakeTime += LM::Timer::lastFrame;
		}

		return true;

	}

	bool Snake::CheckCollision()
	{
		if (GetTailLength() == 0) {
			return false;
		}
		else {
			for (unsigned int i = 0; i < GetTailLength(); i++) {
				if (m_Head.m_position == m_Tail[i].m_position) {
					return true;
				}
			}
			return false;
		}
	}

	void Snake::UpdateTail(const glm::ivec2 &move)
	{
		if (GetTailLength() != 0) {
			for (unsigned int i = m_Tail.size() - 1; i > 0; i--) {
				m_Tail[i].setPosition(m_Tail[i - 1].m_position);
			}
			m_Tail[0].setPosition(m_Head.m_position - move);
		}
	}

	void Snake::SetDirection(EDirection dir)
	{ 
		/*if (m_Direction == 0) {		if (m_Head.m_position.y != m_MaxPos.y - 2)	move = glm::vec3(0, 1, 0); }
		else if (m_Direction == 1) {	if (m_Head.m_position.y != 1)				move = glm::vec3(0, -1, 0); }
		else if (m_Direction == 2) {	if (m_Head.m_position.x != m_MaxPos.x - 2)	move = glm::vec3(1, 0, 0); }
		else {							if (m_Head.m_position.x != 1)				move = glm::vec3(-1, 0, 0); }*/
		if (m_LastDirection == EDirection::UP && dir == EDirection::DOWN || m_LastDirection == EDirection::DOWN && dir == EDirection::UP ||
			m_LastDirection == EDirection::LEFT && dir == EDirection::RIGHT || m_LastDirection == EDirection::RIGHT && dir == EDirection::LEFT){}
		else {
			m_Direction = dir;
		}
	}
}