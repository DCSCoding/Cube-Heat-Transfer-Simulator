#include "Logical_Cube.h"
#include "IronCube.h"

IronCube::IronCube(Cubependium* cubependium) :
	Logical_Cube(273, cubependium)
{}

IronCube::IronCube(float temperature, Cubependium* cubependium) :
	Logical_Cube(temperature, cubependium)
{
	id = 2;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}