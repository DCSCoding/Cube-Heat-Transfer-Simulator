#pragma once

#pragma once
#include "Logical_Cube.h"

class GoldCube : public Logical_Cube {
public:
	GoldCube(Cubependium* cubependium);
	GoldCube(float temperature, Cubependium* cubependium);
};