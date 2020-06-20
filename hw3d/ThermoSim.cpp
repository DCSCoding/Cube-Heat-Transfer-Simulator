// ThermoSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Cube.h"
#include "AirCube.h"
#include <vector>
#include <random>
#include <ctime>
#include <chrono>
#include <thread>
#include "ThermoSim.h"

void update(std::vector<std::vector<std::vector<Cube*>>> cubes);
void updateNeighbors(Cube* cube, std::vector<Cube*> neighbors);

std::vector<std::vector<std::vector<Cube*>>> getNewState()
{
    size_t width = 10;
    size_t length = 10;
    size_t height = 10;
    
    std::vector<std::vector<std::vector<Cube>>> cubes(width, std::vector<std::vector<Cube>>(length, std::vector<Cube>(0)));
	std::vector<std::vector<std::vector<Cube*>>> cubes2(width, std::vector<std::vector<Cube*>>(length, std::vector<Cube*>(height)));
    size_t index = 0;
   
    std::default_random_engine rg(time(0));
    std::uniform_int_distribution<int> random_int(1, 1000);

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
				//std::cout << "Pointer Address: " << cubes2[x][y][z] << " " << cubes2[x][y][z]->getTemperature() << " | " << cubes[x][y][z].getTemperature();
				//std::cout << "\n";

			}
		}
	};
	auto t2 = std::chrono::high_resolution_clock::now();
	
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << "\n";
	
	t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1; i++) {
		update(cubes2);
	}
	t2 = std::chrono::high_resolution_clock::now();

	/*for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			for (int z = 0; z < height; z++) {
				std::cout << (int)cubes2[x][y][z]->getTemperature();
				std::cout << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}*/
	
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    
}

void update(std::vector<std::vector<std::vector<Cube*>>> cubes) {
	for (int x = 0; x < cubes.size(); x++) {
		for (int y = 0; y < cubes[x].size(); y++) {
			for (int z = 0; z < cubes[x][y].size(); z++) {
				std::vector<Cube*> neighbors;
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

void updateNeighbors(Cube* cube, std::vector<Cube*> neighbors) {

	int scaler = 10;

	std::vector<float> transfer_rate;

	for (Cube* c : neighbors) {
		float ctr = cube->getConductivity() * c->getConductivity();
		transfer_rate.push_back(ctr * (cube->getTemperature() - c->getTemperature()) * scaler);
	}

	for (int i = 0; i < neighbors.size(); i++) {
		cube->update(-transfer_rate[i]);
		neighbors[i]->update(transfer_rate[i]);
	}

}

