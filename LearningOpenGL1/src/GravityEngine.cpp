#include "GScene.h"
#include "Application.h"
#include "scenes/Depth_Test_Scene.h"
#include "scenes/Model_Loading_Scene.h"
#include "Fuck.h"

int main()
{
	Scene *depthScene = DepthTestingScene::CreateScene();

	Application app;
	app.runWithScene(depthScene);
	
	return 0;
}

