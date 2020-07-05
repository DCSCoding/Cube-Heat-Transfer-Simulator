#pragma once
#include "Logical_Cube.h"
#include <unordered_map>
class Chunk {
public:
	Chunk(int x, int y, int z, Cubependium* cp);
	Logical_Cube cubes[4096];
	Logical_Cube* pcubes[4096];
	int x_pos;
	int y_pos;
	int z_pos;
	std::unordered_map<Logical_Cube*, std::vector<Logical_Cube*>> neighbor_map;
	void setNeighborMap(Logical_Cube* pcubes[]);
	void setNeighborMap(Logical_Cube* pcubes[], unsigned char step);
	void update(Logical_Cube* pcubes[], unsigned char step);
	void updateNeighbors(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors, std::unordered_map<Logical_Cube*, bool>& has_moved);
	void checkActive(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors);
};