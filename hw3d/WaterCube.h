#pragma once
#include "Logical_Cube.h"

class WaterCube : public Logical_Cube {
public:
	WaterCube(Cubependium* cubependium);
	WaterCube(float temperature, Cubependium* cubependium);

};