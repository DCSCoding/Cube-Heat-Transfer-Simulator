#include "Logical_Cube.h"
#include "WaterCube.h"

WaterCube::WaterCube(Cubependium* cubependium, short position) :
	Logical_Cube(cubependium, position)
{}

WaterCube::WaterCube(float temperature, Cubependium* cubependium, short position) :
	Logical_Cube(temperature, cubependium, position)
{
	id = 6;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}