#pragma once
#include "RenderableObject.h"
class Astroid :
	public RenderableObject
{
public:
	Astroid();
	~Astroid();

	void Update(float deltaTime);
};

