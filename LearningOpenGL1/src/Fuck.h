#pragma once

#include "GScene.h"

class Fuck
{
public:
	friend class GLView;
	friend class Camera;
	friend class Scene;

public:
	Fuck();
	~Fuck();
	static Fuck* getInstance();

	GLView* getGLView();
	Scene*  getRunningScene();
	Camera* getMainCamera();

	void setGLView(GLView *glView);
	void setRunningScene(Scene* scene);
	void setMainCamera(Camera *camera);

	void mainLoop();
	void drawScene();

private:
	static Fuck* _instance;
	GLView* _glView;
	Camera* _mainCamera;
	Scene* _runningScene;
};

