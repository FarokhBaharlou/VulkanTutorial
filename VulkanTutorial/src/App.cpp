#include "App.h"

namespace MyEngine
{
	void App::run()
	{
		while (!window.shouldClose())
		{
			glfwPollEvents();
		}
	}
}