#pragma once
#include "Chunk.h"
#include "Cubependium.h"
#include <unordered_map>
#include <random>
class ThermoSim {
public:

	ThermoSim();
	std::vector<Chunk> chunks;
	Cubependium cp;
	std::unordered_map<Chunk*, std::vector<Chunk*>> chunk_neighbors;
	void addChunk(int x, int y, int z);
	//void update(unsigned char step, int chunk_index);
	void update_all(int chunk_index);
	void update_neighbor_chunks();
	void set_chunk_neighbors();
	std::mt19937 rg;
private:

};