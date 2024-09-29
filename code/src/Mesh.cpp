#include "Mesh.h"
#include <iostream>

extern float meshKd;

void Mesh::Update(float dt)
{
	SetHooksKd();
	ApplyHooks();
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			particles[GetIndex(x, y)].VerletMove(dt);
		}
	}

}
void Mesh::CheckCollisions(SphereObject object)
{
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (particles[GetIndex(x, y)].isStatic)
				continue;
			if (object.Collision(particles[GetIndex(x, y)].lastPosition)) 
			{
				std::pair<glm::vec3, glm::vec3> values = object.Mirror(particles[GetIndex(x, y)].lastPosition, particles[GetIndex(x, y)].velociti);
				particles[GetIndex(x, y)].position = values.first;
				particles[GetIndex(x, y)].velociti= values.second;
			}
		}
	}
}
void Mesh::CheckCollisions(Plane plane)
{
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (particles[GetIndex(x, y)].isStatic)
				continue;
			if (plane.Collision(particles[GetIndex(x, y)].lastPosition, particles[GetIndex(x, y)].position))
			{
				std::pair<glm::vec3, glm::vec3> values = plane.Mirror(particles[GetIndex(x, y)].lastPosition, particles[GetIndex(x, y)].velociti);
				particles[GetIndex(x, y)].position = values.first;
				particles[GetIndex(x, y)].velociti = values.second;
			}
		}
	}
}



void Mesh::RenderUpdate()
{
	int size = width * heigth;
	glm::vec3* positions = new glm::vec3[size];
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			positions[GetIndex(x, y)] = startingPosition + particles[GetIndex(x, y)].position;
		}
	}
	ClothMesh::updateClothMesh(&(positions[0].x));
}

int Mesh::GetIndex(int x, int y)
{
	int index = y * width + x;
	return index;
}

void Mesh::SetStartingPositions()
{
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			particles[GetIndex(x, y)].position = glm::vec3(-5, 5, 5)+ glm::vec3(x, y, -y);
		}
	}
}
void Mesh::SetHooksKd()
{
	for (int i = 0; i < hooks.size(); i++)
	{
		hooks[i]->kd = meshKd;
	}
}
void Mesh::LinkParticles()
{
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			CreateHooks(x, y);
		}
	}
}

void Mesh::ApplyHooks()
{
	for (int i = 0; i < hooks.size(); i++)
	{
		hooks[i]->AddForceToParticle();
	}
}

void Mesh::SetStaticParticles(int w, int h)
{
	for (int y = 0; y < w; y++)
	{
		for (int x = 0; x < h; x++)
		{
			particles[GetIndex(x, y)].isStatic = true;
		}
	}
}
void Mesh::SetStaticParticles()
{
	particles[GetIndex(0, heigth - 1)].isStatic = true;
	particles[GetIndex(width - 1, heigth - 1)].isStatic = true;
}

void Mesh::CreateHooks(int w, int h)
{
	CreateHook(w + 1, h, GetIndex(w, h));
	CreateHook(w, h - 1, GetIndex(w, h));
	CreateHook(w + 1, h + 1, GetIndex(w, h));
	CreateHook(w + 1, h - 1, GetIndex(w, h));
	CreateHook(w + 2, h,GetIndex(w, h));
	CreateHook(w, h - 2,GetIndex(w, h));

}
void Mesh::CreateHook(int w,int h,int aIndex)
{
	Particle* a = &particles[aIndex];
	if (!IsOutOfBounds(w, h)) {
		Particle* b = &particles[GetIndex(w, h)];
		float l = glm::length(a->position - b->position);
		Hook* hook = new Hook(a, b, meshKe, meshKd, l);
		hooks.push_back(hook);
		std::cout << "Linked particles number " << aIndex  << " and " << GetIndex(w, h) << std::endl;
	}
}
bool Mesh::IsOutOfBounds(int w, int h)
{
	if (w >= width || w < 0)
		return true;
	if (h >= heigth || h < 0)
		return true;
	
	return false;
}