#pragma once

#pragma once
#include "Logical_Cube.h"

class InsulatorCube : public Logical_Cube {
public:
	const size_t id = 4;
	InsulatorCube();
	InsulatorCube(float temperature);
};