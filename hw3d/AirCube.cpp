#include "Cube.h"
#include "AirCube.h"

AirCube::AirCube() :
	Cube(273, .0013, .024, 1.0, 0, 0)
{}

AirCube::AirCube(float temperature) :
	Cube(temperature, .0013, .024, 1.0, 0, 0)
{}