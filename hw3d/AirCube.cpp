#include "Logical_Cube.h"
#include "AirCube.h"

AirCube::AirCube(Cubependium* cubependium) :
	Logical_Cube(273, cubependium)
{}

AirCube::AirCube(float temperature, Cubependium* cubependium) :
	Logical_Cube(temperature, cubependium)
{
	id = 4;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}