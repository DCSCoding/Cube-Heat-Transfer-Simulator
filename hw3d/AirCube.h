#pragma once
#include "Logical_Cube.h"

class AirCube: public Logical_Cube{
public:
	AirCube(Cubependium* cubependium, short position);
	AirCube(float temperature, Cubependium* cubependium, short position);
	
};