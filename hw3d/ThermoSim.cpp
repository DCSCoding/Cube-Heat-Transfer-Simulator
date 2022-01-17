
#include "ThermoSim.h"
#include <chrono>


ThermoSim::ThermoSim() 
{
	rg.seed(time(0));
}

void ThermoSim::addChunk(int x, int y, int z)
{
	chunks.emplace_back(Chunk(x, y, z, &cp, rg));
	set_chunk_neighbors();
	
}

//void ThermoSim::update(unsigned char step, int chunk_index)
//{
//	
//		chunks[chunk_index].update(step);
//		chunks[chunk_index].setNeighborMap(step);
//	
//	
//}

void ThermoSim::update_all(int chunk_index)
{

	chunks[chunk_index].update();
	//chunks[chunk_index].updateNeighborMap();

}

void ThermoSim::update_neighbor_chunks()
{
	for (Chunk& chunk : chunks) {
		std::vector<Chunk*> neighbors = chunk_neighbors[&chunk];
		for (Chunk* neighbor : neighbors) {
			if (chunk.x_pos - neighbor->x_pos == 1) {
				for (int i = 0; i < 256; i++) {
					chunk.update_edge_pair(chunk.left_face_cubes[i], neighbor->right_face_cubes[i], &chunk, neighbor);
				}
			}else if(chunk.x_pos - neighbor->x_pos == -1) {
				for (int i = 0; i < 256; i++) {
					chunk.update_edge_pair(chunk.right_face_cubes[i], neighbor->left_face_cubes[i], &chunk, neighbor);
				}
			}
			else if (chunk.y_pos - neighbor->y_pos == 1) {
				for (int i = 0; i < 256; i++) {
					chunk.update_edge_pair(chunk.bottom_face_cubes[i], neighbor->top_face_cubes[i], &chunk, neighbor);
				}
			}
			else if (chunk.y_pos - neighbor->y_pos == -1) {
				for (int i = 0; i < 256; i++) {
					chunk.update_edge_pair(chunk.top_face_cubes[i], neighbor->bottom_face_cubes[i], &chunk, neighbor);
				}
			}
			else if (chunk.z_pos - neighbor->z_pos == 1) {
				for (int i = 0; i < 256; i++) {
					chunk.update_edge_pair(chunk.front_face_cubes[i], neighbor->back_face_cubes[i], &chunk, neighbor);
				}
			}
			else if (chunk.z_pos - neighbor->z_pos == -1) {
				for (int i = 0; i < 256; i++) {
					chunk.update_edge_pair(chunk.back_face_cubes[i], neighbor->front_face_cubes[i], &chunk, neighbor);
				}
			}
			}
		}
	}


void ThermoSim::set_chunk_neighbors()
{
	for (Chunk& chunk : chunks) {
		Chunk* pchunk = &chunk;
		std::vector<Chunk*> neighbors;
		for (Chunk& otherchunk : chunks) {
			if (std::abs(chunk.x_pos - otherchunk.x_pos) == 1 || std::abs(chunk.y_pos - otherchunk.y_pos) == 1 || std::abs(chunk.z_pos - otherchunk.z_pos) == 1) {
				neighbors.emplace_back(&otherchunk);
			}
		}
		chunk_neighbors[pchunk] = neighbors;
	}
}




