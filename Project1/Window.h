#pragma once
#ifndef WINDOW
#define WINDOW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Vector4d.h"

struct WindowCreateInfo
{
	WindowCreateInfo():width(0),
	height(0),
	majorVersion(0),
	minorVersion(0),
	title()
	{}
	uint32_t width;
	uint32_t height;
	uint32_t majorVersion;
	uint32_t minorVersion;
	std::string title;
};


class Window
{
public:
	friend GLFWAPI GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun callback);
	Window(const WindowCreateInfo &WindowCreateInfo);
public:
	GLFWwindow* GetWindowHandle();
	void run();
	void setClearColor(double r,double g,double b,double a);
protected:
	static void resize(GLFWwindow* window, int width, int height);
private:
	GLFWwindow* InitWindow();
private:
	GLFWwindow* mWindowHandle;
	WindowCreateInfo mWindowCreateInfo;
	Vector4d mClearColor;
	static uint32_t width;
	static uint32_t height;
};
#endif


