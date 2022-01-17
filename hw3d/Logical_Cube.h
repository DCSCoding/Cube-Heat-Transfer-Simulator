#pragma once
#include "Cubependium.h"
#include <memory> 
class Logical_Cube {
public:
	Logical_Cube();
	Logical_Cube(Cubependium*, short position);
	float getConductivity();
	float getTemperature();
	float getSpecificHeat();
	float getMass();
	float getDensity();
	float getEnergyContent();
	float getEnergyContent(float temp);
	float getMeltingPoint();
	float getBoilingPoint();
	unsigned char getState();
	short getType();
	short getIndex();
	void setEnergyContent(float energy);
	void setType(size_t type);
	void setActive(bool activity_flag);
	void updateTemperature();
	void update(float energy);
	bool isActive();
	Cubependium* cp;
protected:
	short pos;
	bool active = true;
	short id = 0;
	unsigned char state;
	float temperature;
	float energy_content;
	Logical_Cube(float temperature, Cubependium*, short position);
	void setState(float temperature);
};