#pragma once

#pragma once
#include "Logical_Cube.h"

class GoldCube : public Logical_Cube {
public:
	const size_t id = 1;
	GoldCube();
	GoldCube(float temperature);
};