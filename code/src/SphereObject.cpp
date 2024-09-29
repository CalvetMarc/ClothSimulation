#include "SphereObject.h"

SphereObject::SphereObject(glm::vec3 _position, int _r) : CollisionableObject(_position)
{
	radius = _r;
	renderSphere = true;
};

bool SphereObject::Collision(glm::vec3 p)
{
	float distance = glm::length(p - position);
	return(distance <= radius);
}

void SphereObject::Update()
{
	Sphere::updateSphere(position,radius);
}

std::pair<glm::vec3, glm::vec3> SphereObject::Mirror(glm::vec3 p2, glm::vec3 v2)
{
	//mejorar punto de collision
	glm::vec3 normal = glm::normalize(p2 - position);
	float d = -(p2.x * normal.x + p2.y * normal.y + p2.z * normal.z);
	Plane p = Plane(normal, d);
	return (p.Mirror(p2, v2));
}

