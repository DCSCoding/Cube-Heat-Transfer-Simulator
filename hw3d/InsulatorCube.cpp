#include "Logical_Cube.h"
#include "InsulatorCube.h"

InsulatorCube::InsulatorCube() :
	Logical_Cube(273)
{}

InsulatorCube::InsulatorCube(float temperature) :
	Logical_Cube(temperature)
{}