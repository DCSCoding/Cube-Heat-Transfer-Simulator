#include "Cube.h"
#include "InsulatorCube.h"

InsulatorCube::InsulatorCube() :
	Cube(273, 19.3, 1.2, 0.0, 10000, 100000)
{}

InsulatorCube::InsulatorCube(float temperature) :
	Cube(temperature, 19.3, 1.2, 0.0, 10000, 100000)
{}