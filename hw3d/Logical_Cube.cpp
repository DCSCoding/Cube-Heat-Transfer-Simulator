#include "Logical_Cube.h"
#include <iostream>

Logical_Cube::Logical_Cube() :
	density(1.0),
	volume(1000000),
	mass(density * volume),
	conductivity(10.0),
	specific_heat(1),
	melting_point(373),
	boiling_point(573),
	temperature(273),
	energy_content(mass*specific_heat*temperature)
	{
	setState(temperature);
	}

Logical_Cube::Logical_Cube(float temperature, float density, float conductivity, float specific_heat, float melting_point, float boiling_point) :
	temperature(temperature),
	density(density),
	conductivity(conductivity),
	specific_heat(specific_heat),
	melting_point(melting_point),
	boiling_point(boiling_point),
	volume(1000000),
	mass(density* volume)

{
	energy_content = mass * specific_heat * temperature;
	setState(temperature);
	}

float Logical_Cube::getConductivity() {
	return conductivity;
	}

float Logical_Cube::getTemperature() {
	return temperature;
	}

float  Logical_Cube::getSpecificHeat() {
	return specific_heat;
	}

float  Logical_Cube::getMass() {
	return mass;
	}

float  Logical_Cube::getDensity() {
	return density;
	}

float  Logical_Cube::getEnergyContent() {
	return energy_content;
	}

float  Logical_Cube::getEnergyContent(float temp) {
	//Returns this Logical_Cubes energy content at a given temperature.
	return mass * specific_heat * temp;
	}

size_t  Logical_Cube::getState() {
	return state;
	}

void  Logical_Cube::setState(float temperature) {
	if (temperature > boiling_point) {
		state = 2;
		}
	else if (temperature > melting_point) {
		state = 1;
		}
	else {
		state = 0;
		}
	}

void Logical_Cube::update(float energy) {
		//System.out.println("Adding " + energy);
		float m = temperature;
		energy_content += energy;
		temperature = energy_content / mass / specific_heat;
		setState(temperature);

}
