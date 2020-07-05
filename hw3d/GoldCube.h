#pragma once

#pragma once
#include "Logical_Cube.h"

class GoldCube : public Logical_Cube {
public:
	GoldCube(Cubependium* cubependium, short position);
	GoldCube(float temperature, Cubependium* cubependium, short position);
};