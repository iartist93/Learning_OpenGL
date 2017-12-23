#pragma once

#include <string>

class Scene
{
public:
	virtual void render();
	virtual void clear();
	virtual bool init();
	virtual std::string name();
};
