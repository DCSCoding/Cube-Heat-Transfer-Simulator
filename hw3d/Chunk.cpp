#include "Chunk.h"
#include <random>
#include <chrono>
#include "GoldCube.h"
Chunk::Chunk(int x, int y, int z, Cubependium* cp) :
	x_pos(x), y_pos(y), z_pos(z)
{
	std::default_random_engine rg(time(0));
	std::uniform_int_distribution<int> random_int(450, 500);
	size_t index = 0;
	//For now, creates an array of gold cubes.
	//Todo: Add a parameter to decide what the chunk should generate. 
	for (short i = 0; i < 4096; i++) {
		cubes[i] = GoldCube(273, cp, i);
		pcubes[i] = &cubes[i];
	};

	
}

void Chunk::setNeighborMap(Logical_Cube* pcubes[])
{
	std::random_device rg;
	std::mt19937 g(rg());

	for (short i = 0; i < 4096; i++) {
		std::vector<Logical_Cube*> neighbors;
		//first adds the top cube to the neighbor list.
		if (i + 16 < 4096) neighbors.emplace_back(pcubes[i + 16]);
		//adds the laterally adjacent cubes to the neighbor list.
		if (i + 256 < 4096) neighbors.emplace_back(pcubes[i + 256]);
		if (i + 1 < 4096) neighbors.emplace_back(pcubes[i + 1]);
		if (i - 256 >= 0) neighbors.emplace_back(pcubes[i - 256]);
		if (i - 1 >= 0) neighbors.emplace_back(pcubes[i - 1]);
		//adds the bottom cube to the neighbor list.
		if (i - 16 >= 0) neighbors.emplace_back(pcubes[i - 16]);

		//Shuffling the neighbor order
		if (i + 16 < 4096 && i - 16 >= 0) {
			//If there is a top and bottom neighbor, shuffles positions 1-4 (lateral neighbors)
			std::shuffle(neighbors.begin() + 1, neighbors.end() - 1, g);
		}
		else if (i + 16 > 4096) {
			//If there is no top cube, shuffle from 0-4
			std::shuffle(neighbors.begin(), neighbors.end() - 1, g);
		}

		neighbor_map[pcubes[i]] = neighbors;

	}
};


void Chunk::setNeighborMap(Logical_Cube* pcubes[], unsigned char step)
{
	std::random_device rg;
	std::mt19937 g(rg());
	short end = (step + 1) * 64;
	short start = end - 64;

	for (short i = start; i < end; i++) {
		std::vector<Logical_Cube*> neighbors;
		//first adds the top cube to the neighbor list.
		if (i + 16 < 4096) neighbors.emplace_back(pcubes[i + 16]);
		//adds the laterally adjacent cubes to the neighbor list.
		if (i + 256 < 4096) neighbors.emplace_back(pcubes[i + 256]);
		if (i + 1 < 4096) neighbors.emplace_back(pcubes[i + 1]);
		if (i - 256 >= 0) neighbors.emplace_back(pcubes[i - 256]);
		if (i - 1 >= 0) neighbors.emplace_back(pcubes[i - 1]);
		//adds the bottom cube to the neighbor list.
		if (i - 16 >= 0) neighbors.emplace_back(pcubes[i - 16]);

		//Shuffling the neighbor order
		if (i + 16 < 4096 && i - 16 >= 0) {
			//If there is a top and bottom neighbor, shuffles positions 1-4 (lateral neighbors)
			std::shuffle(neighbors.begin() + 1, neighbors.end() - 1, g);
		}
		else if (i + 16 > 4096) {
			//If there is no top cube, shuffle from 0-4
			std::shuffle(neighbors.begin(), neighbors.end() - 1, g);
		}

		neighbor_map[pcubes[i]] = neighbors;

	}

}

void Chunk::update(Logical_Cube* pcubes[], unsigned char step)
{
	std::vector<Logical_Cube*> neighbors;
	std::unordered_map<Logical_Cube*, bool> has_moved;
	
	short end = (step + 1) * 64;
	short start = end - 64;

	for (short i = start; i < end; i++) {
		if (pcubes[i]->isActive()) {
			updateNeighbors(pcubes[i], neighbor_map[pcubes[i]], has_moved);
		}
		else {
			checkActive(pcubes[i], neighbor_map[pcubes[i]]);
		}
	}
	
}

void Chunk::updateNeighbors(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors, std::unordered_map<Logical_Cube*, bool>& has_moved)
{
	int scaler = 8;
	bool has_difference = false;

	std::vector<float> transfer_rate;
	for (Logical_Cube* c : neighbors) {

		float ctr = cube->getConductivity() * c->getConductivity() * scaler;
		transfer_rate.emplace_back(ctr * (cube->getTemperature() - c->getTemperature()));
		if (abs(cube->getTemperature() - c->getTemperature()) > 1) {
			has_difference = true;
		}
		if (!has_difference) {
			cube->setActive(false);
			return;
		}
	}

	for (int i = 0; i < neighbors.size(); i++) {
		cube->update(-transfer_rate[i]);
		neighbors[i]->update(transfer_rate[i]);

		if (i < 4 && has_moved[cube] == false && cube->getState() > 0 && cube->getState() >= neighbors[i]->getState() && cube->getTemperature() > neighbors[i]->getTemperature() && cube->getDensity() <= neighbors[i]->getDensity() && neighbors[i]->isActive()) {
			size_t temp_type = cube->getType();
			float temp_energy_content = cube->getEnergyContent();
			cube->setType(neighbors[i]->getType());
			cube->setEnergyContent(neighbors[i]->getEnergyContent());
			neighbors[i]->setType(temp_type);
			neighbors[i]->setEnergyContent(temp_energy_content);
			cube->updateTemperature();
			neighbors[i]->updateTemperature();
			has_moved[cube] = true;
			has_moved[neighbors[i]] = true;
		}


	}



}

void Chunk::checkActive(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors)
{
	if (cube->getType() == 3) {
		return;
	}
	for (Logical_Cube* c : neighbors) {
		if (abs(c->getTemperature() - cube->getTemperature()) > 1) {
			cube->setActive(true);
			return;
		}
	}

	cube->setActive(false);
}
