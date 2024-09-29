#pragma once
#include "Particle.h"
#include <glm\glm.hpp>
#include "Simulator.h"
#include <vector>
#include <cmath>
#include "SphereObject.h"


extern bool renderCloth;
namespace ClothMesh {
	extern void updateClothMesh(float* array_data);
	extern const int numCols;
	extern const int numRows;
};
struct Hook
{
	Hook(Particle* _a, Particle* _b, float _ke, float _kd,float _l) : a(_a), b(_b), ke(_ke),kd(_kd),l(_l) {};

	Particle* a;
	Particle* b;
	float ke;
	float kd;
	float l;

	void AddForceToParticle()
	{
		
		float distance = glm::length(a->position - b->position);
		float distanceDif = (distance - l);

		glm::vec3 direction = a->position - b->position;
		glm::vec3 normalized = glm::vec3(0, 0, 0);
		if(glm::length(direction.x) != 0)
			 normalized = glm::normalize(direction);

		glm::vec3  velocitys = glm::vec3(0, 0, 0);
		glm::vec3 vDir = a->velociti - b->velociti;
		if (glm::length(vDir) != 0)
			velocitys = glm::normalize(vDir);
		glm::vec3 force = -(ke * distanceDif + (kd * velocitys)* normalized) * normalized;
	
			a->force += force;
			b->force -= force;
	}
};
class Mesh
{
public:
	int width;
	int heigth;
	glm::vec3 startingPosition;
	Particle* particles;
	std::vector<Hook*> hooks;
	float meshKd;
	float meshKe;

	Mesh(glm::vec3 _startingPosition,float _meshKd, float _meshKe)
	{
		width = ClothMesh::numCols;
		heigth = ClothMesh::numRows;
		renderCloth = true;
		int size = width * heigth;
		particles = new Particle[size];
		meshKd = _meshKd;
		meshKe = _meshKe;

		SetStartingPositions();
		SetStaticParticles();
		LinkParticles();
	}
	void Update(float dt);
	void RenderUpdate();

	void SetHooksKd();
	int GetIndex(int x, int y);
	void SetStartingPositions();
	void SetStaticParticles(int w, int h);
	void SetStaticParticles();
	void CreateHooks(int w, int h);
	bool IsOutOfBounds(int w, int h);
	void LinkParticles();
	void ApplyHooks();
	void CreateHook(int w, int h, int aIndex);
	void CheckCollisions(SphereObject object);
	void CheckCollisions(Plane plane);
};

