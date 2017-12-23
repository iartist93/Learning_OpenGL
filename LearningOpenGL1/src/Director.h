#pragma once

#include "GScene.h"

class Director
{
public:
	Director();
	~Director();
	friend class GLView;
	friend class Camera;

public:
	static Director* getInstance();
	
	GLView* getGLView();
	Scene*  getRunningScene();
	Camera* getMainCamera();

	void setGLView(GLView *glView);
	void setRunningScene(Scene* scene);
	void setMainCamera(Camera *camera);

	void mainLoop();
	void drawScene();

private:
	static Director* _instane;

	GLView* _glView;
	Camera* _mainCamera;
	Scene* _runningScene;
};

