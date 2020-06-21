// ThermoSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Logical_Cube.h"
#include "AirCube.h"
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include "ThermoSim.h"
#include <iostream>


ThermoSim::ThermoSim(size_t width1, size_t length1, size_t height1) :
	width(width1), length(length1), height(height1), cubes(width, std::vector<std::vector<Logical_Cube>>(length, std::vector<Logical_Cube>(0))),
		cubes2(width1, std::vector<std::vector<Logical_Cube*>>(length1, std::vector<Logical_Cube*>(height1)))

{
	
	//std::vector<std::vector<std::vector<Logical_Cube>>> cubes(width, std::vector<std::vector<Logical_Cube>>(length, std::vector<Logical_Cube>(0)));
	//std::vector<std::vector<std::vector<Logical_Cube*>>> cubes2(width, std::vector<std::vector<Logical_Cube*>>(length, std::vector<Logical_Cube*>(height)));
	
	std::default_random_engine rg(time(0));
	std::uniform_int_distribution<int> random_int(1, 1000);
	//std::cout << cubes.size();
	size_t index = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			for (int z = 0; z < height; z++) {
				cubes[x][y].push_back(AirCube(random_int(rg)));
				index++;
			}
		}
	};
	auto t1 = std::chrono::high_resolution_clock::now();
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			for (int z = 0; z < height; z++) {
				cubes2[x][y][z] = &cubes[x][y][z];

			}
		}
	};
	
	
}
void ThermoSim::getNewState(std::vector<std::vector<std::vector<Logical_Cube>>> cubes, std::vector<std::vector<std::vector<Logical_Cube*>>> cubes2)
{
    
	auto t1 = std::chrono::high_resolution_clock::now();
	
	update(cubes2);
	
	auto t2 = std::chrono::high_resolution_clock::now();

	//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    
}

void ThermoSim::update(std::vector<std::vector<std::vector<Logical_Cube*>>> cubes) {
	for (int x = 0; x < cubes.size(); x++) {
		for (int y = 0; y < cubes[x].size(); y++) {
			for (int z = 0; z < cubes[x][y].size(); z++) {
				std::vector<Logical_Cube*> neighbors;
				if (x - 1 >= 0) {
					if (y - 1 >= 0) {
						neighbors.push_back(cubes[x - 1][y - 1][z]);
						if (z - 1 >= 0) neighbors.push_back(cubes[x - 1][y - 1][z - 1]);
						if (z + 1 < cubes[x][y].size()) neighbors.push_back(cubes[x - 1][y - 1][z + 1]);
					}

					neighbors.push_back(cubes[x - 1][y][z]);
					if (z - 1 >= 0) neighbors.push_back(cubes[x - 1][y][z - 1]);
					if (z + 1 < cubes[x][y].size()) neighbors.push_back(cubes[x - 1][y][z + 1]);

					if (y + 1 < cubes[x].size()) {
						neighbors.push_back(cubes[x - 1][y + 1][z]);
						if (z - 1 >= 0) neighbors.push_back(cubes[x - 1][y + 1][z - 1]);
						if (z + 1 < cubes[x][y].size()) neighbors.push_back(cubes[x - 1][y + 1][z + 1]);
					}
				}

				if (y - 1 >= 0) {
					neighbors.push_back(cubes[x][y - 1][z]);
					if (z - 1 >= 0) neighbors.push_back(cubes[x][y - 1][z - 1]);
					if (z + 1 < cubes[x][y].size())neighbors.push_back(cubes[x][y - 1][z + 1]);
				}

				if (z - 1 >= 0) neighbors.push_back(cubes[x][y][z - 1]);
				if (z + 1 < cubes[x][y].size()) neighbors.push_back(cubes[x][y][z + 1]);

				if (y + 1 < cubes[x].size()) {
					neighbors.push_back(cubes[x][y + 1][z]);
					if (z - 1 >= 0) neighbors.push_back(cubes[x][y + 1][z - 1]);
					if (z + 1 < cubes[x][y].size()) neighbors.push_back(cubes[x][y + 1][z + 1]);
				}

				if (x + 1 < cubes.size()) {

					if (y - 1 >= 0) {
						neighbors.push_back(cubes[x + 1][y - 1][z]);
						if (z - 1 >= 0) neighbors.push_back(cubes[x + 1][y - 1][z - 1]);
						if (z + 1 < cubes[x][y].size()) neighbors.push_back(cubes[x + 1][y - 1][z + 1]);
					}

					neighbors.push_back(cubes[x + 1][y][z]);
					if (z - 1 >= 0) neighbors.push_back(cubes[x + 1][y][z - 1]);
					if (z + 1 < cubes[x][y].size()) neighbors.push_back(cubes[x + 1][y][z + 1]);

					if (y + 1 < cubes[x].size()) {
						neighbors.push_back(cubes[x + 1][y + 1][z]);
						if (z - 1 >= 0) neighbors.push_back(cubes[x + 1][y + 1][z - 1]);
						if (z + 1 < cubes[x][y].size()) neighbors.push_back(cubes[x + 1][y + 1][z + 1]);
					}
				}

				updateNeighbors(cubes[x][y][z], neighbors);

			}
		}
	}
}

void ThermoSim::updateNeighbors(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors) {

	int scaler = 10;

	std::vector<float> transfer_rate;

	for (Logical_Cube* c : neighbors) {
		float ctr = cube->getConductivity() * c->getConductivity();
		transfer_rate.push_back(ctr * (cube->getTemperature() - c->getTemperature()) * scaler);
	}

	for (int i = 0; i < neighbors.size(); i++) {
		cube->update(-transfer_rate[i]);
		neighbors[i]->update(transfer_rate[i]);
	}

}

