#pragma once

#include <GL/glew.h>
#include <gtx/transform.hpp>
#include "renderable2d.h"

namespace LM {

	class Renderer2D
	{
	protected:
		virtual void submit(const Renderable2D *renderable) = 0;
		virtual void flush() = 0;
	};

}