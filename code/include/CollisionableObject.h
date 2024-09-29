#pragma once
#include "Plane.h"
#include <utility>
class CollisionableObject
{
public:
	glm::vec3 position;
	CollisionableObject();
	CollisionableObject(glm::vec3 _position);
	virtual bool Collision(glm::vec3 p);
	virtual void Update();
	void virtual SetRender(bool state);
	virtual std::pair<glm::vec3, glm::vec3> Mirror(glm::vec3 p2, glm::vec3 v2);
};

