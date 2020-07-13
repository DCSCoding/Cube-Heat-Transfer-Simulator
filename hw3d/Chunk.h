#pragma once
#include "Logical_Cube.h"
#include <unordered_map>
#include <random>
class Chunk {
public:
	Chunk(int x, int y, int z, Cubependium* cp, std::mt19937& rand);
	Logical_Cube cubes[4096];
	Logical_Cube* pcubes[4096];
	int x_pos;
	int y_pos;
	int z_pos;
	std::mt19937& rg;
	Logical_Cube* top_face_cubes[256];
	Logical_Cube* bottom_face_cubes[256];
	Logical_Cube* front_face_cubes[256];
	Logical_Cube* back_face_cubes[256];
	Logical_Cube* left_face_cubes[256];
	Logical_Cube* right_face_cubes[256];
	std::unordered_map<Logical_Cube*, bool> has_moved;
	std::unordered_map<Logical_Cube*, std::vector<Logical_Cube*>> neighbor_map;
	void setNeighborMap();
	void setNeighborMap(unsigned char step);
	void update(unsigned char step);
	void update();
	void update_edge_pair(Logical_Cube* cube, Logical_Cube* neighbor, Chunk* chunk, Chunk* neighbor_chunk);
	void updateNeighbors(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors, std::unordered_map<Logical_Cube*, bool>& has_moved);
	void checkActive(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors);
};