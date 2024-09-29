#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <cstdio>

#include "MeshSimulation.h"


#pragma region simulationSelection
enum class EnabledSimulation {
	MESH_SIMULATOR,
};

Simulator* currentSimulator;
EnabledSimulation currentSimulation;
void setSimulation(EnabledSimulation simulation) {
	if (currentSimulation == simulation) {
		return;
	}

	delete currentSimulator;
	currentSimulation = simulation;
	switch (simulation) {
		case EnabledSimulation::MESH_SIMULATOR:
			printf("Start the Moving Cape");
			currentSimulator = new MeshSimulation();
			break;
		;;
	}
}
#pragma endregion

#pragma region GUI
bool show_test_window = false;
void GUI() {
	bool show = true;
	
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Mecanica")) {
			if (ImGui::MenuItem("Practica 1")) { setSimulation(EnabledSimulation::MESH_SIMULATOR); };

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("Physics Parameters", &show, 100);//100 es grandaria
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		
		currentSimulator->RenderGui();
	}

	
	
	ImGui::End();
}

#pragma endregion


void PhysicsInit() {
	// The default simulation
	currentSimulator = new MeshSimulation();
	currentSimulation = EnabledSimulation::MESH_SIMULATOR;
}

void PhysicsUpdate(float dt) {
	currentSimulator->Update(dt);
	currentSimulator->RenderUpdate();
}

void PhysicsCleanup() {
	delete currentSimulator;
}