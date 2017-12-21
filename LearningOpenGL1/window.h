#pragma once

#include <GLFW/glfw3.h>

class Window
{
private:
	static Window* _instance;

public:
	int width = 800;
	int height = 600;
	GLFWwindow *glfwWindow;

public:
	static Window* MainWindow();

public:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void Init();
};