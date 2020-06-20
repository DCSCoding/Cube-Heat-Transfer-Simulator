#include "Logical_Cube.h"
#include "InsulatorCube.h"

InsulatorCube::InsulatorCube() :
	Logical_Cube(273, 19.3, 1.2, 0.0, 10000, 100000)
{}

InsulatorCube::InsulatorCube(float temperature) :
	Logical-Cube(temperature, 19.3, 1.2, 0.0, 10000, 100000)
{}