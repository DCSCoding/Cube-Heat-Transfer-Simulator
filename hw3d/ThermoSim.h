#pragma once
#include "Logical_Logical_Cube.h"

class ThermoSim {
public:
	ThermoSim(size_t width, size_t length, size_t height);
	void getNewState(std::vector<std::vector<std::vector<Logical_Cube>>> Logical_CubeStateMap, std::vector<std::vector<std::vector<Logical_Cube*>>> Logical_Cubes2);
	size_t width;
	size_t length;
	size_t height;
	std::vector<std::vector<std::vector<Logical_Cube>>> Logical_Cubes;
	std::vector<std::vector<std::vector<Logical_Cube*>>> Logical_Cubes2;
private:
	void update(std::vector<std::vector<std::vector<Logical_Cube*>>> Logical_Cubes);
	void updateNeighbors(Logical_Cube* Logical_Cube, std::vector<Logical_Cube*> neighbors);

};