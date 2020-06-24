#pragma once
#include "Logical_Cube.h"

class IronCube : public Logical_Cube {
public:
	const size_t id = 3;
	IronCube();
	IronCube(float temperature);
};