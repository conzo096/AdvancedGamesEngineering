#pragma once
#include "RenderableObject.h"
class Bullet: public RenderableObject
{
public:
	Bullet();
	~Bullet();

	virtual void Update(float deltaTime);
	bool toBeDeleted =false;
	std::string belongsTo;
	float speed;
};

