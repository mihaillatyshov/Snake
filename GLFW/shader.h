#pragma once

#include <iostream>
#include <vector>
#include "fileutils.h"
#include <GL/glew.h>
#include <gtx/transform.hpp>

namespace LM {

	class Shader
	{
	private:
		GLuint m_ShaderID;
		const char *m_VertPath;
		const char *m_FragPath;
	public:
		Shader(const char *vertPath, const char *fragPath);
		~Shader();

		void enable() const;
		void disable() const;


		void setUniformMat4(const GLchar* name, const glm::mat4& matrix);
		void setUniform1f(const GLchar* name, float value);
		void setUniform2f(const GLchar* name, const glm::vec2 &vector);
		void setUniform3f(const GLchar* name, const glm::vec3 &vector);
		void setUniform4f(const GLchar* name, const glm::vec4 &vector);
		void setUniform1i(const GLchar* name, int value);
	private:
		GLint getUniformLocation(const GLchar *name);
		GLuint load();
	};

}