#include "Window.h"
#include "Camera.h"
#include "Scene.h"

int main()
{
	WindowCreateInfo createInfo;
	createInfo.majorVersion = 4;
	createInfo.minorVersion = 6;
	createInfo.width = 800;
	createInfo.height = 800;
	createInfo.title = "window";
	Window *window = new Window(createInfo);
	window->setClearColor(0, 0, 0, 1);
	window->run();
	return 0;
}