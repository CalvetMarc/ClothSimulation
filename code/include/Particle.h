#pragma once
#include <glm\glm.hpp>
#include <vector>
class Particle
{
public:

	Particle() { acceleration = glm::vec3(0, -9.81, 0); };
	Particle(glm::vec3 _position) : position(_position) {
		velociti = glm::vec3(0, 0, 0);
		acceleration = glm::vec3(0, 0, 0);
	}
	Particle(glm::vec3 _position, glm::vec3 _velociti) : position(_position), velociti(_velociti) {
		acceleration = glm::vec3(0, 0, 0);
	}
	Particle(glm::vec3 _position, glm::vec3 _velociti, glm::vec3 _acceleration) : position(_position), velociti(_velociti), acceleration(_acceleration) {}

	bool isStatic = false;
	float mass = 1;
	float mu = 1;
	glm::vec3 force;
	glm::vec3 lastPosition;
	glm::vec3 position;
	glm::vec3 velociti;
	glm::vec3 acceleration;

	void EulerMove(float dt);
	void VerletMove(float dt);

};