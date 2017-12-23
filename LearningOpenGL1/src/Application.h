#pragma once

#include "GScene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Fuck.h"
#include "camera.h"
#include "GLView.h"


class Application
{
public:
	Application();
	~Application();

	void run();
	void runWithScene(Scene* scene);
	void calcluateDeltaTime();

public:
	float deltaTime;

private:
	float lastFrame;
};