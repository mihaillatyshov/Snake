#pragma once


#include <GL/glew.h>
#include <glfw3.h>

namespace LM {

#define MAX_KEYS		1024
#define MAX_BUTTONS		32

	class Window
	{
	private:
		// Window name
		const char *m_Title;

		// Window width
		int m_Width;

		// Window height
		int m_Height;

		// Pointer to window
		GLFWwindow *m_Window;

		// Window state
		bool m_Closed;

		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		double mx, my;

	public:
		Window(const char* title, int width, int height);
		~Window();

		// Clear opengl buffers
		void clear() const;

		// Poll events 
		// Swap buffers
		void update();

		// Need to close window
		bool closed() const;

		// Return window width 
		inline int getWidth() const { return m_Width; }

		// Return window height
		inline int getHeight() const { return m_Height; }

		// Return the value of the pressed key
		bool isKeyPressed(unsigned int keycode) const;

		// Return the value of the pressed button
		bool isMouseButtonPressed(unsigned int button) const;

		// Return the value of the mouse position
		void getMousePosition(double &x, double &y) const;
	private:
		// Initialize glfw
		// Initialize glew
		// Initialize background color
		// Creating window
		bool init();

		// Check keyboard
		friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

		// Check mouse
		friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
		
		// Check cursor position
		friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
	};

}