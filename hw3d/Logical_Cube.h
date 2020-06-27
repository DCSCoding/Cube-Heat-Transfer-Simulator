#pragma once
#include "Cubependium.h"
#include <memory> 
class Logical_Cube {
public:
	Logical_Cube();
	Logical_Cube(Cubependium*);
	float getConductivity();
	float getTemperature();
	float getSpecificHeat();
	float getMass();
	float getDensity();
	float getEnergyContent();
	float getEnergyContent(float temp);
	size_t getState();
	size_t id = 0;
	void update(float energy);
	Cubependium* cp;
protected:
	size_t state;
	float temperature;
	float energy_content;
	Logical_Cube(float temperature, Cubependium*);
	void setState(float temperature);
};