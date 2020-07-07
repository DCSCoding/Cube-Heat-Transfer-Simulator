#pragma once
#include "Chunk.h"
#include "Cubependium.h"
#include <unordered_map>
class ThermoSim {
public:
	ThermoSim();
	std::vector<Chunk> chunks;
	Cubependium cp;
	void addChunk(int x, int y, int z);
	void update(unsigned char step, int chunk_index);
	void update_all(int chunk_index);
	/*void update(std::vector<std::vector<std::vector<Logical_Cube*>>> cubes);*/
private:

};