#pragma once
#include <glm/glm.hpp>
#include "ParticleSystem.h"
#define PI 3.14159265
class ParticleEmissor
{
protected:
	float currentTime = 0;
	int maxParticles = 0;
public:
	float speedMagnitude = 5;
	float rate;
	float lifetime;
	glm::vec3 position;
	glm::vec3 speed;
	ParticleSystem *particleSystem;
	ParticleEmissor(int maxParticles, float _rate, float _lifeTime);
	virtual void Update(float dt);
	virtual void CalculateInitialSpeed();
	virtual glm::vec3 GetRandomPosition();
	virtual int GetNumberOfParticlesAlive() { return rate * lifetime; }
	float RandomNumber(float Min, float Max);
};

