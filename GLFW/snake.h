#pragma once



#include <vector>
#include "fruit.h"

namespace LM {

	class Snake
	{
	public:
		enum EDirection {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};
	private:
		struct Section{
			glm::ivec2 m_position;
			Sprite m_sprite;
			Section (const glm::ivec2 &position) :
				m_position(position),
				m_sprite(Sprite(m_position.x + 0.05f, m_position.y + 0.05f, 0.9f, 0.9f, glm::vec4(0, 0, 1, 1))) {}
			void addPosition(const glm::ivec2 &vector) {
				m_position += vector;
				m_sprite.addPosition(glm::vec3(vector.x, vector.y, 0));
			}
			void setPosition(const glm::ivec2 &position) {
				m_position = position;
				m_sprite.setPosition(glm::vec3(position.x + 0.05f, position.y + 0.05f, 0));
			}
		};

		
		float m_SnakeTime;
		EDirection m_Direction = EDirection::UP;
		EDirection m_LastDirection = EDirection::UP;
		//unsigned short m_Direction = 0;
		//unsigned short m_LastDirection = 0;
	public:
		glm::ivec2 m_MaxPos;
		Section m_Head;
		std::vector<Section> m_Tail;
	public:
		Snake(const glm::ivec2 &position, const glm::ivec2 &maxPos);
		unsigned int GetTailLength() { return m_Tail.size(); }
		bool update(Fruit* fruit);
		void SetDirection(EDirection dir);
	private:
		void UpdateTail(const glm::ivec2 &move);
		bool CheckCollision();
	};

}