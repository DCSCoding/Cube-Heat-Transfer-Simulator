#include "Logical_Cube.h"
#include "InsulatorCube.h"

InsulatorCube::InsulatorCube(Cubependium* cubependium, short position) :
	Logical_Cube(cubependium, position)
{}

InsulatorCube::InsulatorCube(float temperature, Cubependium* cubependium, short position) :
	Logical_Cube(temperature, cubependium, position)
{
	id = 3;
	active = false;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}