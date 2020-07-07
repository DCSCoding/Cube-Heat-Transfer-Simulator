// ThermoSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <thread>
#include "ThermoSim.h"


ThermoSim::ThermoSim() 
{
	chunks.reserve(10);
}

void ThermoSim::addChunk(int x, int y, int z)
{
	Chunk chonk(x, y, z, &cp);
	chunks.emplace_back(chonk);
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




