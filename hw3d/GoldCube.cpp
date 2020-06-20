#include "Logical_Cube.h"
#include "GoldCube.h"

GoldCube::GoldCube() :
	Logical_Cube(273, 19.3, .129, 314, 1064+273, 2700+273)
{}

GoldCube::GoldCube(float temperature) :
	Logical_Cube(temperature, 19.3, .129, 314, 1064+273, 2700+273)
{}