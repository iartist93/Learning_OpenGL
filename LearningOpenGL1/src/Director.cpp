#include "Director.h"
#include <iostream>



Director::Director()
{

}


Director::~Director()
{
}


Director* Director::_instane = nullptr;

Director* Director::getInstance()
{
	if (_instane)
	{
		_instane = new Director;
	}
	std::cout << "-------------? this " << &_instane << std::endl;

	return _instane;
}

GLView* Director::getGLView()
{
	return _glView;
}

Scene* Director::getRunningScene()
{
	return _runningScene;
}

void Director::setGLView(GLView * glView)
{
	_glView = glView;
}

void Director::setRunningScene(Scene * scene)
{
	_runningScene = scene;
}

void Director::setMainCamera(Camera * camera)
{
	_mainCamera = camera;
}

Camera * Director::getMainCamera()
{
	return _mainCamera;
}

void Director::mainLoop()
{
	drawScene();
}

void Director::drawScene()
{
	_runningScene->render();
}
