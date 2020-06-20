#pragma once
#include "Cube.h"

class ThermoSim {
public:
	ThermoSim(size_t width, size_t length, size_t height);
	void getNewState(std::vector<std::vector<std::vector<Cube>>> cubeStateMap, std::vector<std::vector<std::vector<Cube*>>> cubes2);
	size_t width;
	size_t length;
	size_t height;
	std::vector<std::vector<std::vector<Cube>>> cubes;
	std::vector<std::vector<std::vector<Cube*>>> cubes2;
private:
	void update(std::vector<std::vector<std::vector<Cube*>>> cubes);
	void updateNeighbors(Cube* cube, std::vector<Cube*> neighbors);

};