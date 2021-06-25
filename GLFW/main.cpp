#include <iostream>
#include "window.h"
#include "shader.h"
#include <gtx/transform.hpp>

#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

#include "renderer2d.h"
#include "simple2drenderer.h"
#include "batchrenderer2d.h"
#include "static_sprite.h"
#include "sprite.h"
#include "timer.h"

#include "boundingsphere.h"
#include "aabb.h"
#include "plane.h"
#include "sat.h"
#include "myaabb.h"
#include "obb.h"
#include "obbnew.h"
#include "EpsilonOBB.h"


#include "snake.h"
#include "fruit.h"

#include <ctime>


#define M_PI            3.14159265358979323846


#define PHYSICS_TEST	false
#define BATCH_RENDERER	true

// Set up ortho projection width and height
#define ORTHO_WIDTH		32.0f
#define ORTHO_HEIGHT	18.0f

// Set up window width and height
#define WIDTH 960
#define HEIGHT 540

float LM::Timer::lastFrame = 0.0f;
float LM::Timer::time = 0.0f;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Create window
	LM::Window window("Test", WIDTH, HEIGHT);




#if PHYSICS_TEST
	LM::BoundingSphere Player(glm::vec3(0.0f, 94.0f, 0.0f), 45.0f);

	LM::Plane TopPlane(glm::vec3(0.0f, 1.0f, 0.0f), -50.0f);
	LM::Plane BottomPlane(glm::vec3(0.0f, -1.0f, 0.0f), -50.0f);

	LM::IntersectData test1 = TopPlane.IntersectSphere(Player);
	LM::IntersectData test2 = BottomPlane.IntersectSphere(Player);

	std::cout << "Test1: Intersected: " << test1.GetDoesIntersect() << ", Distance: " << test1.GetDistance() << std::endl;
	std::cout << "Test2: Intersected: " << test2.GetDoesIntersect() << ", Distance: " << test2.GetDistance() << std::endl;

	LM::Sat sat1(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 3.0f, 0.0f), glm::vec3(3.0f, 3.0f, 0.0f));
	sat1.movePoints(glm::vec3(-4.0f, 0.0f, 0.0f));
	LM::Sat sat2(glm::vec3(1.0f, 2.0f, 0.0f), glm::vec3(3.0f, 4.0f, 0.0f), glm::vec3(5.0f, 4.0f, 0.0f));

	LM::Line lines[] = {
		LM::Line(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
		LM::Line(glm::vec3(1.0f, 3.0f, 0.0f), glm::vec3(3.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
		LM::Line(glm::vec3(3.0f, 3.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f))
	};

	LM::Sat satTest(lines, 3);


	LM::MyAABB AABB1(glm::vec2(1, 1), glm::vec2(4, 4));
	LM::MyAABB AABB2(glm::vec2(3, 3), glm::vec2(5, 7));

	std::cout << "\n\n\n";

	LM::EpsilonOBB eOBB1(glm::vec3(0, 0, 0), glm::vec3(2, 2, 2));
	LM::EpsilonOBB eOBB2(glm::vec3(2, 0, 0), glm::vec3(2, 2, 2));

	std::cout << LM::TestOBBOBB(eOBB1, eOBB2) << std::endl;

	LM::OBB_2 obb1(glm::dvec2(1.0, 3.0), glm::dvec3(3, 4, 0), glm::dvec3(60, 0, 0));
	LM::OBB_2 obb2(glm::dvec2(1.0, 2.0), glm::dvec3(3, 3, 0), glm::dvec3(45, 0, 0));
	LM::OBB_2 obb3(glm::dvec2(7.0, 1.0), glm::dvec3(4, 2, 0), glm::dvec3(10, 0, 0));



	/*LM::OBB obb1(1, 3, glm::translate(glm::vec3(3, 7, 0)) * glm::rotate((float)M_PI / 4, glm::vec3(0, 0, 1)));

	LM::OBB obb2(1, 2, glm::translate(glm::vec3(3.2, 8.2f, 0)) * glm::rotate((float)M_PI / 6, glm::vec3(0, 0, 1)));*/

#endif




	//glm::mat4 orthoProjection = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	glm::mat4 orthoProjection = glm::ortho(0.0f, ORTHO_WIDTH, 0.0f, ORTHO_HEIGHT, -1.0f, 1.0f);


	LM::Shader shader("res/basic.vert", "res/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", orthoProjection);

	std::vector<LM::Renderable2D*> sprites;

	srand(time(NULL));
	
	
	for (float y = 0; y < ORTHO_HEIGHT; y += 1) {
		for (float x = 0; x < ORTHO_WIDTH; x += 1) {
			if (x == 0 || y == 0 || x == ORTHO_WIDTH - 1 || y == ORTHO_HEIGHT - 1)
				sprites.push_back(new LM::Sprite(x + 0.05f, y + 0.05f, 0.9f, 0.9f, glm::vec4(1, 0, 0, 1)));
		}
	}

	//sprites.push_back(new LM::Sprite(4 + 0.05f, 5 + 0.05f, 0.9f, 0.9f, glm::vec4(0, 1, 0, 1)));

#if BATCH_RENDERER
	LM::Sprite sprite(5, 5, 4, 4, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	LM::Sprite sprite2(7, 1, 2, 3, glm::vec4(0.2f, 0.0f, 1.0f, 1.0f));
	LM::BatchRenderer2D renderer;
#else
	LM::StaticSprite sprite(5, 5, 4, 4, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	LM::StaticSprite sprite2(7, 1, 2, 3, glm::vec4(0.2f, 0.0f, 1.0f, 1.0f), shader);
	LM::Simple2DRenderer renderer;
#endif


	shader.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));




	LM::Timer time, loopTime;
	float timer = 0;
	unsigned int frames = 0;
	double x = 2, y = 2;

	LM::Snake snake1(glm::ivec2(3, 3), glm::ivec2 (ORTHO_WIDTH, ORTHO_HEIGHT));
	LM::Fruit fruit;

	// Create main(game) loop
	while (!window.closed()) {

		loopTime.reset();
		window.clear();
		window.getMousePosition(x, y);
		if (window.isKeyPressed(87)) snake1.SetDirection(LM::Snake::EDirection::UP);
		if (window.isKeyPressed(65)) snake1.SetDirection(LM::Snake::EDirection::LEFT);
		if (window.isKeyPressed(83)) snake1.SetDirection(LM::Snake::EDirection::DOWN);
		if (window.isKeyPressed(68)) snake1.SetDirection(LM::Snake::EDirection::RIGHT);


#if PHYSICS_TEST
		sat1.movePoints(glm::vec3(0.01f, 0.0f, 0.0f));

		AABB1.setAABB(glm::vec2((float)(x * ORTHO_WIDTH / WIDTH), float(ORTHO_HEIGHT - y * ORTHO_HEIGHT / HEIGHT)));

		obb2.setLocation(glm::dvec3((float)(x * ORTHO_WIDTH / WIDTH), float(ORTHO_HEIGHT - y * ORTHO_HEIGHT / HEIGHT), 0));
		obb1.simulate();

		std::cout << obb3.intersectOOB(obb1) << std::endl;
		std::cout << obb3.intersectOOB(obb2) << std::endl;
		std::cout << obb2.intersectOOB(obb1) << std::endl;
		obb1.draw();
		obb2.draw();
		obb3.draw();

		/*obb2.setTransform(glm::translate(glm::vec3((float)(x * ORTHO_WIDTH / WIDTH), float(ORTHO_HEIGHT - y * ORTHO_HEIGHT / HEIGHT), 0)) * 
						  glm::rotate((float)M_PI / 6, glm::vec3(0, 0, 1)));

		obb1.intersectOOB(obb2);
		*/

		//std::cout << AABB1.Intersection(AABB2) << std::endl;;
			
		//sat1.IntersectSAT(sat2);
#else
		if (!snake1.update(&fruit)) break;
		/*if (snakeTime >= 0.5f) {
			if (snakeDirection == 0)
				((LM::Sprite*)sprites[sprites.size() - 1])->addPosition(glm::vec3(0, 1, 0));
			else if (snakeDirection == 1)
				((LM::Sprite*)sprites[sprites.size() - 1])->addPosition(glm::vec3(0, -1, 0));
			else if (snakeDirection == 2)
				((LM::Sprite*)sprites[sprites.size() - 1])->addPosition(glm::vec3(1, 0, 0));
			else
				((LM::Sprite*)sprites[sprites.size() - 1])->addPosition(glm::vec3(-1, 0, 0));

			snakeTime = 0;
		}
		else {
			snakeTime += LM::Timer::lastFrame;
		}*/



		shader.setUniform2f("light_pos", glm::vec2(snake1.m_Head.m_position.x, snake1.m_Head.m_position.y) + glm::vec2(0.45f, 0.45f));
		//shader.setUniform2f("light_pos", glm::vec2((float)x, (float)y));
#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++) {
			renderer.submit(sprites[i]);
		}
		for (int i = 0; i < snake1.GetTailLength(); i++) {
			renderer.submit(&snake1.m_Tail[i].m_sprite);
		}
		renderer.submit(&fruit.m_sprite);
		renderer.submit(&snake1.m_Head.m_sprite);
		

#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();
#endif


		window.update();


		frames++;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
		LM::Timer::time = time.elapsed();
		LM::Timer::lastFrame = loopTime.elapsed();
	}
	
	return 0;
}