#include "GScene.h"
#include "Application.h"
#include "scenes/DepthTestScene.h"
#include "Fuck.h"

int main()
{
	Scene *depthScene = DepthTestScene::CreateScene();

	Application app;
	app.runWithScene(depthScene);
	
	return 0;
}

