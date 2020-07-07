#include "Logical_Cube.h"
#include "AirCube.h"

AirCube::AirCube(Cubependium* cubependium, short position) :
	Logical_Cube(cubependium, position)
{}

AirCube::AirCube(float temperature, Cubependium* cubependium, short position) :
	Logical_Cube(temperature, cubependium, position)
{
	id = 4;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}