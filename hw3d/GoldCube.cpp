#include "Logical_Cube.h"
#include "GoldCube.h"

GoldCube::GoldCube(Cubependium* cubependium, short position) :
	Logical_Cube(cubependium, position)
{}

GoldCube::GoldCube(float temperature, Cubependium* cubependium, short position) :
	Logical_Cube(temperature, cubependium, position)
{
	id = 1;
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
}