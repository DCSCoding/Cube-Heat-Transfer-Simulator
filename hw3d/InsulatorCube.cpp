#include "Logical_Cube.h"
#include "InsulatorCube.h"

InsulatorCube::InsulatorCube(Cubependium* cubependium) :
	Logical_Cube(273, cubependium)
{}

InsulatorCube::InsulatorCube(float temperature, Cubependium* cubependium) :
	Logical_Cube(temperature, cubependium)
{
	id = 3;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}