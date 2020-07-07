#include "Logical_Cube.h"
#include "IronCube.h"

IronCube::IronCube(Cubependium* cubependium, short position) :
	Logical_Cube(cubependium, position)
{}

IronCube::IronCube(float temperature, Cubependium* cubependium, short position) :
	Logical_Cube(temperature, cubependium, position)
{
	id = 2;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}