#pragma once
#include "Simulator.h"
#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include "Mesh.h"
#include "Particle.h"
#include "CollisionableObject.h"
#include <vector>

class MeshSimulation : public Simulator
{
public:
	MeshSimulation();
	glm::vec3 startingPosition;
	Mesh* mesh;
	SphereObject* object;
	Plane* floor;
	float currentTime = 0;
	float resetTime = 20;
	float collisionDelay = 0.1f;

	virtual void Update(float dt) override;
	virtual void RenderUpdate() override;
	virtual void RenderGui() override;
};

