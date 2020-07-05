#pragma once
#include "Logical_Cube.h"

class IronCube : public Logical_Cube {
public:
	IronCube(Cubependium* cubependium, short position);
	IronCube(float temperature, Cubependium* cubependium, short position);
};