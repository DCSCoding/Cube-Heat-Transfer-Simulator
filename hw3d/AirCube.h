#pragma once
#include "Logical_Cube.h"

class AirCube: public Logical_Cube{
public:
	const size_t id = 2;
	AirCube();
	AirCube(float temperature);
	
};