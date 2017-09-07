#pragma once
#include "RenderableObject.h"
class Bullet: public RenderableObject
{
public:
	Bullet();
	~Bullet();

	void Update(float deltaTime);
	bool toBeDeleted =false;
	std::string belongsTo;
};

