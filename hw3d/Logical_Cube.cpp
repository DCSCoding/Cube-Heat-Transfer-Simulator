#include "Logical_Cube.h"
#include <iostream>

Logical_Cube::Logical_Cube() :
temperature(273)
{

}
Logical_Cube::Logical_Cube(Cubependium* cubependium) :
	temperature(273),
	cp(cubependium)
{
	
	setState(temperature);
	}

Logical_Cube::Logical_Cube(float temperature, Cubependium* cubependium) :
	temperature(temperature),
	cp(cubependium)
{
	energy_content = cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temperature;
	setState(temperature);
	}

float Logical_Cube::getConductivity() {
	return cp->getTypeData(id).conductivity;
	}

float Logical_Cube::getTemperature() {
	return temperature;
	}

float  Logical_Cube::getSpecificHeat() {
	return cp->getTypeData(id).specific_heat;
	}

float  Logical_Cube::getMass() {
	return cp->getTypeData(id).mass;
	}

float  Logical_Cube::getDensity() {
	return cp->getTypeData(id).density;
	}

float  Logical_Cube::getEnergyContent() {
	return energy_content;
	}

float  Logical_Cube::getEnergyContent(float temp) {
	//Returns this Logical_Cubes energy content at a given temperature.
	return cp->getTypeData(id).mass * cp->getTypeData(id).specific_heat * temp;
	}

size_t  Logical_Cube::getState() {
	return state;
	}

void  Logical_Cube::setState(float temperature) {
	if (temperature > cp->getTypeData(id).boiling_point) {
		state = 2;
		}
	else if (temperature > cp->getTypeData(id).melting_point) {
		state = 1;
		}
	else {
		state = 0;
		}
	}

void Logical_Cube::update(float energy) {
		
		energy_content += energy;
		temperature = energy_content / cp->getTypeData(id).mass / cp->getTypeData(id).specific_heat;
		setState(temperature);

}
