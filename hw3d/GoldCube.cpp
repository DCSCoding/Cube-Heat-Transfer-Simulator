#include "Logical_Cube.h"
#include "GoldCube.h"

GoldCube::GoldCube(Cubependium* cubependium) :
	Logical_Cube(273, cubependium)
{}

GoldCube::GoldCube(float temperature, Cubependium* cubependium) :
	Logical_Cube(temperature, cubependium)
{
	id = 1;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}