#pragma once
#include "Cubependium.h"
class Logical_Cube {
public:
	Logical_Cube();
	float getConductivity();
	float getTemperature();
	float getSpecificHeat();
	float getMass();
	float getDensity();
	float getEnergyContent();
	float getEnergyContent(float temp);
	size_t getState();
	const size_t id = 0;
	void update(float energy);
	Cubependium cp;
protected:
	size_t state;
	float temperature;
	float energy_content;
	Logical_Cube(float temperature);
	void setState(float temperature);
};