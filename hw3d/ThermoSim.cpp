#include <thread>
#include "ThermoSim.h"


ThermoSim::ThermoSim() 
{
	chunks.reserve(10);
}

void ThermoSim::addChunk(int x, int y, int z)
{
	chunks.emplace_back(Chunk(x, y, z, &cp));
}

void ThermoSim::update(unsigned char step, int chunk_index)
{
	
		chunks[chunk_index].update(step);
		chunks[chunk_index].setNeighborMap(step);
	
	
}

void ThermoSim::update_all(int chunk_index)
{

	chunks[chunk_index].update();
	chunks[chunk_index].setNeighborMap();


}




