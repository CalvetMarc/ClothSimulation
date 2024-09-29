#include "Particle.h"

void Particle::EulerMove(float dt)
{
	/*
	if (isStatic)
		return;

    force -= velociti * mu;

	force.y += -9.81;
    acceleration = force / mass;

	lastPosition =  glm::vec3(position.x, position.y, position.z);
	velociti = velociti + acceleration * dt;

	position = position + velociti * dt;

	force = glm::vec3(0, 0, 0);
	acceleration = glm::vec3(0, 0, 0);
	*/
	
}

void Particle::VerletMove(float dt)
{
	if (isStatic)
		return;
	force.y += -9.81;

	lastPosition = glm::vec3(position.x, position.y, position.z);

	position = position + (position - lastPosition) + ((force * 1500.f)/mass) * (dt * dt);

	force = glm::vec3(0, 0, 0);
}
