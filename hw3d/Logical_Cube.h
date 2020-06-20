#pragma once

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
	
	void update(float energy);
protected:
	size_t state;
	float temperature;
	float energy_content;
	const float volume;
	const float mass;
	const float density;
	const float conductivity;
	const float specific_heat;
	const float melting_point;
	const float boiling_point;
	Logical_Cube(float temperature, float density, float conductivity, float specific_heat, float melting_point, float boiling_point);

	void setState(float temperature);
};