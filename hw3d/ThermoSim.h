#pragma once
#include "Logical_Cube.h"

class ThermoSim {
public:
	ThermoSim(size_t width, size_t length, size_t height);
	void getNewState(std::vector<std::vector<std::vector<Logical_Cube>>> cubes, std::vector<std::vector<std::vector<Logical_Cube*>>> cubes2);
	size_t width;
	size_t length;
	size_t height;
	long duration = 0;
	std::vector<std::vector<std::vector<Logical_Cube>>> cubes;
	std::vector<std::vector<std::vector<Logical_Cube*>>> cubes2;
	void update(std::vector<std::vector<std::vector<Logical_Cube*>>> cubes);
	
private:
	void updateNeighbors(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors);
	

};