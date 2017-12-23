#include "Application.h"
#include "shader.h"

Application::Application()
{
	deltaTime = 0.0f;
	lastFrame = 0.0f;

	auto director = Fuck::getInstance();
	auto glView = director->getGLView();
	auto mainCamera = director->getMainCamera();

	if (!glView)
	{
		glView = new GLView("Gravity Engine", 800, 600, false);
		director->setGLView(glView);	
	}

	if (!mainCamera)
	{
		mainCamera = new Camera();
		director->setMainCamera(mainCamera);
	}
}


Application::~Application()
{
}

void Application::run()
{
	auto director = Fuck::getInstance();
	auto glView = director->getGLView();
	auto runningScene = director->getRunningScene();

	runningScene->init();

	std::cout << runningScene->name() << std::endl;

	while (!glView->windowShouldClose())
	{
		calcluateDeltaTime();

		Input::ProcessKeyboard(glView->glfwWindow, deltaTime);

		runningScene->clear();		// VERY IMPOTANT
		director->mainLoop();

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cerr << "OpenGL error: " << err << std::endl;
		}

		glView->swpapBuffer();
		glView->pollEvents();
	}
	
	glView->terminate();
}


void Application::runWithScene(Scene * scene)
{

	auto director = Fuck::getInstance();
	auto glView = director->getGLView();

	director->setRunningScene(scene);
	run();
}

void Application::calcluateDeltaTime()
{
	deltaTime = glfwGetTime() - lastFrame;
	lastFrame = glfwGetTime();
}