#pragma once
#include "Logical_Cube.h"

class IronCube : public Logical_Cube {
public:
	IronCube(Cubependium* cubependium);
	IronCube(float temperature, Cubependium* cubependium);
};