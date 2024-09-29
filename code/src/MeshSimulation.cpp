#include "MeshSimulation.h"
#include "SphereObject.h"
#include <glm\glm.hpp>

extern bool renderSphere;
bool resetScene = false;
bool collisionWithFloor = false;

float meshKd = 0.8f;
float meshKe = 100.f;

void MeshSimulation::Update(float dt)
{
	int steps = 60;
	currentTime += dt;
	for (int i = 0; i < steps; i++)
	{
		if (resetScene == true)
		{
			currentTime = resetTime + 5;
			resetScene = false;
			continue;
		}

		if (currentTime >= collisionDelay)
		{
			if (renderSphere) {
				mesh->CheckCollisions(*object);
			}
			if (collisionWithFloor){
				mesh->CheckCollisions(*floor);
			}
			
		}
		mesh->Update(dt/steps);
	}
	if (currentTime >= resetTime) 
	{
		startingPosition = mesh->startingPosition;
		mesh = new Mesh(glm::vec3(0, 0, 0), meshKd, meshKe);
		if (renderSphere) {
			object = new SphereObject(object->position, object->radius);
		}
		
		floor = new Plane(0, 1, 0, 0);
		currentTime = 0;
	}
}

void MeshSimulation::RenderUpdate()
{
	if (renderSphere) {
		object->Update();
	}
	
	mesh->RenderUpdate();

}

void MeshSimulation::RenderGui()
{
	ImGui::TextColored(ImVec4(255,200,200,5), "P2 Cloth");
	ImGui::Text("The Simultaion reset for each 20 seconds");
	ImGui::Checkbox("Reset Simulation NOW", &resetScene);
	
	ImGui::SliderFloat(
		"Kd",		//label
		&meshKd,	// where the value exists
		-10000,				// min
		10000			// max
	);
	ImGui::SliderFloat(
		"Ke",		//label
		&meshKe,	// where the value exists
		20,				// min
		400			// max
	);
	/*
	ImGui::SliderFloat(
		"Shear",		//label
		&cone->rate,	// where the value exists
		0,				// min
		500				// max
	);
	ImGui::SliderFloat(
		"Bend",			//label
		&cone->rate,	// where the value exists
		0,				// min
		500				// max
	);
	*/
	
	ImGui::InputFloat3(
		"Cape Position",
		&mesh->startingPosition.x
	);
	ImGui::SliderFloat(
		"Cape X",
		&mesh->startingPosition.x, // pointer to an array of 3 floats
		-20,
		20
	);
	ImGui::SliderFloat(
		"Cape Y",
		&mesh->startingPosition.y, // pointer to an array of 3 floats
		-20,
		20
	);
	ImGui::SliderFloat(
		"Cape Z",
		&mesh->startingPosition.z, // pointer to an array of 3 floats
		-20,
		20
	);
	ImGui::Checkbox("Show Sphere", &renderSphere);
	if (renderSphere)
	{
		ImGui::InputFloat3(
			"Sphere Position",
			&object->position.x
		);
		ImGui::SliderFloat(
			"Sphere X",
			&object->position.x, // pointer to an array of 3 floats
			-20,
			20
		);
		ImGui::SliderFloat(
			"Sphere Y",
			&object->position.y, // pointer to an array of 3 floats
			-20,
			20
		);
		ImGui::SliderFloat(
			"Sphere Z",
			&object->position.z, // pointer to an array of 3 floats
			-20,
			20
		);
		ImGui::SliderInt(
			"Sphere Radius",
			&object->radius, // pointer to an array of 3 floats
			-20,
			20
		);
	}
	
	ImGui::Checkbox("Show Collision with Floor", &collisionWithFloor);

	

	
	
}
MeshSimulation::MeshSimulation()
{
	startingPosition = glm::vec3(0, 5, 0);
	mesh = new Mesh(glm::vec3(0,0,0),meshKd, meshKe);
	object = new SphereObject(glm::vec3(+3, 0, 0), 2);
	floor = new Plane(0, 1, 0, 0);
}


