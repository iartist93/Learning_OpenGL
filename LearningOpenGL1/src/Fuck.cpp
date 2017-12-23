#include "Fuck.h"



Fuck::Fuck()
{
	_glView = nullptr;
	_mainCamera = nullptr;
	_runningScene = nullptr;
}


Fuck::~Fuck()
{
}

Fuck* Fuck::_instance = nullptr;

Fuck* Fuck::getInstance()
{
	if (!_instance)
	{
		_instance = new Fuck();
	}
	return _instance;
}



GLView* Fuck::getGLView()
{
	return _glView;
}

Scene* Fuck::getRunningScene()
{
	return _runningScene;
}

void Fuck::setGLView(GLView * glView)
{
	_glView = glView;
}

void Fuck::setRunningScene(Scene * scene)
{
	_runningScene = scene;
}

void Fuck::setMainCamera(Camera * camera)
{
	_mainCamera = camera;
}

Camera * Fuck::getMainCamera()
{
	return _mainCamera;
}

void Fuck::mainLoop()
{
	drawScene();
}

void Fuck::drawScene()
{
	_runningScene->render();
}



