#pragma once

#pragma once
#include "Logical_Cube.h"

class InsulatorCube : public Logical_Cube {
public:
	InsulatorCube(Cubependium* cubependium, short position);
	InsulatorCube(float temperature, Cubependium* cubependium, short position);
};