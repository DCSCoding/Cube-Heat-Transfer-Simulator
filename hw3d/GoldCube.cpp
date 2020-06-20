#include "Cube.h"
#include "GoldCube.h"

GoldCube::GoldCube() :
	Cube(273, 19.3, .129, 314, 1064+273, 2700+273)
{}

GoldCube::GoldCube(float temperature) :
	Cube(temperature, 19.3, .129, 314, 1064+273, 2700+273)
{}