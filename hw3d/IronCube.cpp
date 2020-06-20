#include "Cube.h"
#include "IronCube.h"

IronCube::IronCube() :
	Cube(273, 7.9, .45, 79.5, 1538+273, 2862+273)
{}

IronCube::IronCube(float temperature) :
	Cube(temperature, 7.9, .45, 79.5, 1538 + 273, 2862 + 273)
{}