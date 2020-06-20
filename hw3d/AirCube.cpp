#include "Logical_Cube.h"
#include "AirCube.h"

AirCube::AirCube() :
	Logical_Cube(273, .0013, .024, 1.0, 0, 0)
{}

AirCube::AirCube(float temperature) :
	Logical_Cube(temperature, .0013, .024, 1.0, 0, 0)
{}