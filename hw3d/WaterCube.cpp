#include "Logical_Cube.h"
#include "WaterCube.h"

WaterCube::WaterCube(Cubependium* cubependium) :
	Logical_Cube(273, cubependium)
{}

WaterCube::WaterCube(float temperature, Cubependium* cubependium) :
	Logical_Cube(temperature, cubependium)
{
	id = 6;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}