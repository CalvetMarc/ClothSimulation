#pragma once
#include "CollisionableObject.h"
#pragma region auxiliar
extern bool renderSphere;
namespace Sphere
{
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
}
class SphereObject : public CollisionableObject
{
public:
	int radius;
	SphereObject(glm::vec3 _position,int _r);
	virtual bool Collision(glm::vec3 p) override;
	virtual void Update() override;
	virtual std::pair<glm::vec3, glm::vec3> Mirror(glm::vec3 p2, glm::vec3 v2) override;
	virtual void SetRender(bool state) override { renderSphere = state; }

};

