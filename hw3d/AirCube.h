#pragma once
#include "Logical_Cube.h"

class AirCube: public Logical_Cube{
public:
	AirCube(Cubependium* cubependium);
	AirCube(float temperature, Cubependium* cubependium);
	
};