#pragma once
#include <iostream>

class Simulator {
public:
	virtual void Update(float dt) = 0;
	virtual void RenderUpdate() = 0;
	virtual void RenderGui() = 0;

	virtual ~Simulator() {};
};