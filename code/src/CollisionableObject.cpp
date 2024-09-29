#include "CollisionableObject.h"

CollisionableObject::CollisionableObject()
{
}

CollisionableObject::CollisionableObject(glm::vec3 _position)
{
	position = _position;
}

bool CollisionableObject::Collision(glm::vec3 lastPosition)
{
	return false;
}

void CollisionableObject::Update()
{
}

void CollisionableObject::SetRender(bool state)
{

}

std::pair<glm::vec3, glm::vec3> CollisionableObject::Mirror(glm::vec3 p2, glm::vec3 v2)
{
	return std::pair<glm::vec3, glm::vec3>(0,0);
}
