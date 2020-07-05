// ThermoSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Logical_Cube.h"
#include "AirCube.h"
#include "GoldCube.h"
#include "IronCube.h"
#include "WaterCube.h"
#include "InsulatorCube.h"
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
	std::uniform_int_distribution<int> random_int(450, 500);
	//std::cout << cubes.size();
	size_t index = 0;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			for (int z = 0; z < height; z++) {
				//random water 
				/*if (y < 3) {
					cubes[x][y].emplace_back(WaterCube(random_int(rg), &cp));
				}
				else if (y < 16){
					cubes[x][y].emplace_back(WaterCube(274, &cp));
				}*/
				/*else {
					cubes[x][y].emplace_back(GoldCube(274, &cp));
				}*/
				//iron heat source, gold heat pipe, water basin
				if ((z >= 5 && z <= 9 && y >= 5 && y <= 12 && x >= 1 && x <= 5) && !(z == 7 && y == 6 && x == 3)) {
					cubes[x][y].emplace_back(WaterCube(274, &cp, 0));
				}
				else if ((z == 7 && y == 5 && x == 3) || (z == 7 && y == 6 && x == 3)) {
					cubes[x][y].emplace_back(GoldCube(273, &cp, 0));
				}
				else if ((z == 7 && y == 4 && x >= 3 && x <= 9)) {
					cubes[x][y].emplace_back(GoldCube(273, &cp, 0));
				}
				else if ((z == 7 && y == 5 && x == 9)) {
					cubes[x][y].emplace_back(GoldCube(273, &cp, 0));
				}
				else if ((z >= 6 && z <= 8 && y >= 6 && y <= 8 && x >= 8 && x <= 10)) {
					cubes[x][y].emplace_back(IronCube(10000, &cp, 0));
				}
				else {
					cubes[x][y].emplace_back(InsulatorCube(0, &cp, 0));
				}
				//cubes[x][y].emplace_back(AirCube(100, &cp));
				index++;
			}
		}
	};
	
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < length; y++) {
			for (int z = 0; z < height; z++) {
				cubes2[x][y][z] = &cubes[x][y][z];

			}
		}
	};
	
	setNeighborMap(cubes2);
	
}
//void ThermoSim::getNewState(std::vector<std::vector<std::vector<Logical_Cube>>> cubes, std::vector<std::vector<std::vector<Logical_Cube*>>> cubes2)
//{
//    update(cubes2);
//	   
//}

//void ThermoSim::update(std::vector<std::vector<std::vector<Logical_Cube*>>> cubes) {
//	for (int x = 0; x < cubes.size(); x++) {
//		for (int y = 0; y < cubes[x].size(); y++) {
//			for (int z = 0; z < cubes[x][y].size(); z++) {
//				std::vector<Logical_Cube*> neighbors;
//				if (x - 1 >= 0) {
//					if (y - 1 >= 0) {
//						neighbors.emplace_back(cubes[x - 1][y - 1][z]);
//						if (z - 1 >= 0) neighbors.emplace_back(cubes[x - 1][y - 1][z - 1]);
//						if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x - 1][y - 1][z + 1]);
//					}
//
//					neighbors.emplace_back(cubes[x - 1][y][z]);
//					if (z - 1 >= 0) neighbors.emplace_back(cubes[x - 1][y][z - 1]);
//					if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x - 1][y][z + 1]);
//
//					if (y + 1 < cubes[x].size()) {
//						neighbors.emplace_back(cubes[x - 1][y + 1][z]);
//						if (z - 1 >= 0) neighbors.emplace_back(cubes[x - 1][y + 1][z - 1]);
//						if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x - 1][y + 1][z + 1]);
//					}
//				}
//
//				if (y - 1 >= 0) {
//					neighbors.emplace_back(cubes[x][y - 1][z]);
//					if (z - 1 >= 0) neighbors.emplace_back(cubes[x][y - 1][z - 1]);
//					if (z + 1 < cubes[x][y].size())neighbors.emplace_back(cubes[x][y - 1][z + 1]);
//				}
//
//				if (z - 1 >= 0) neighbors.emplace_back(cubes[x][y][z - 1]);
//				if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x][y][z + 1]);
//
//				if (y + 1 < cubes[x].size()) {
//					neighbors.emplace_back(cubes[x][y + 1][z]);
//					if (z - 1 >= 0) neighbors.emplace_back(cubes[x][y + 1][z - 1]);
//					if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x][y + 1][z + 1]);
//				}
//
//				if (x + 1 < cubes.size()) {
//
//					if (y - 1 >= 0) {
//						neighbors.emplace_back(cubes[x + 1][y - 1][z]);
//						if (z - 1 >= 0) neighbors.emplace_back(cubes[x + 1][y - 1][z - 1]);
//						if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x + 1][y - 1][z + 1]);
//					}
//
//					neighbors.emplace_back(cubes[x + 1][y][z]);
//					if (z - 1 >= 0) neighbors.emplace_back(cubes[x + 1][y][z - 1]);
//					if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x + 1][y][z + 1]);
//
//					if (y + 1 < cubes[x].size()) {
//						neighbors.emplace_back(cubes[x + 1][y + 1][z]);
//						if (z - 1 >= 0) neighbors.emplace_back(cubes[x + 1][y + 1][z - 1]);
//						if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x + 1][y + 1][z + 1]);
//					}
//				}
//
//				updateNeighbors(cubes[x][y][z], neighbors);
//
//			}
//		}
//	}
//
//}

void ThermoSim::updateAdjacent(std::vector<std::vector<std::vector<Logical_Cube*>>> cubes, unsigned char step) {
	std::vector<Logical_Cube*> neighbors;
	std::unordered_map<Logical_Cube*, bool> has_moved;
	/*for (int x = 0; x < cubes.size(); x++) {
		for (int y = 0; y < cubes[x].size(); y++) {
			for (int z = 0; z < cubes[x][y].size(); z++) {
				neighbors = neighbor_map[cubes[x][y][z]];
				if (cubes[x][y][z]->active) {
					
					updateNeighbors(cubes[x][y][z], neighbors, has_moved);
				}
				else {
					checkActive(cubes[x][y][z], neighbors);
				}
				
			}
		}
	}*/

	//will go between 0 and 4 over 64 steps
	int x = (step) / 4;
	//will go between 0 and 16 through 64 steps
	int y_start = (step * 4) % 16 ;
	int y_end = y_start + 4;
	//Each cycle, will update 4 * 16 = 64 blocks. 
	for (int y = y_start; y < y_end; y++) {
		for (int z = 0; z < cubes[x][y].size(); z++) {
			if (x == 15) {
				x = 15;
			}
			if (cubes[x][y][z]->isActive()) {
				updateNeighbors(cubes[x][y][z], neighbor_map[cubes[x][y][z]], has_moved);
			}
			else {
				checkActive(cubes[x][y][z], neighbor_map[cubes[x][y][z]]);
				
			}

		}
	}
	
	has_moved.clear();
	
}

void ThermoSim::updateNeighbors(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors, std::unordered_map<Logical_Cube*, bool>& has_moved) {

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

void ThermoSim::setNeighborMap(std::vector<std::vector<std::vector<Logical_Cube*>>> cubes) {
	std::random_device rg;
	std::mt19937 g(rg());

	for (int x = 0; x < cubes.size(); x++) {
		for (int y = 0; y < cubes[x].size(); y++) {
			for (int z = 0; z < cubes[x][y].size(); z++) {
				std::vector<Logical_Cube*> neighbors;
				//The first cube on the neighbor list is going to be the one above the cube. This makes it so that I don't have to store positonal data in cubes
				//(yet) for the purpose of "moving" hotter liquid/gas cubes upwards.
				//2020/06/30: This system doesn't work right now because list are of variable size. Derp.
				if (y + 1 < cubes[x].size()) neighbors.emplace_back(cubes[x][y + 1][z]);
				
				if (x + 1 < cubes.size()) neighbors.emplace_back(cubes[x + 1][y][z]);
				if (x - 1 >= 0) neighbors.emplace_back(cubes[x - 1][y][z]);
				if (z - 1 >= 0) neighbors.emplace_back(cubes[x][y][z - 1]);
				if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x][y][z + 1]);
				
				if (y - 1 >= 0) neighbors.emplace_back(cubes[x][y - 1][z]);

				if (y + 1 < cubes[x].size() && y - 1 >= 0) {
					std::shuffle(neighbors.begin() + 1, neighbors.end() - 1, g);
				}else if (y + 1 > cubes[x].size()) {
					std::shuffle(neighbors.begin(), neighbors.end() - 1, g);
				}
				else if (y - 1 < 0) {
					std::shuffle(neighbors.begin() + 1, neighbors.end(), g);
				}

				neighbor_map[cubes[x][y][z]] = neighbors;

			}
		}
	}

	
}

void ThermoSim::setNeighborMap(std::vector<std::vector<std::vector<Logical_Cube*>>> cubes, unsigned char step)
{
	std::random_device rg;
	std::mt19937 g(rg());
	//will go between 0 and 4 over 64 steps
	int x = (step) / 4;
	//will go between 0 and 16 through 64 steps
	int y_start = (step * 4) % 16;
	int y_end = y_start + 4;
	if (x == 15) {
		x = 15;
	}
	//Each cycle, will update 4 * 16 = 64 blocks. 
		for (int y = y_start; y < y_end; y++) {
			for (int z = 0; z < cubes[x][y].size(); z++) {
				std::vector<Logical_Cube*> neighbors;
				//The first cube on the neighbor list is going to be the one above the cube. This makes it so that I don't have to store positonal data in cubes
				//(yet) for the purpose of "moving" hotter liquid/gas cubes upwards.
				//2020/06/30: This system doesn't work right now because list are of variable size. Derp.
				if (y + 1 < cubes[x].size()) neighbors.emplace_back(cubes[x][y + 1][z]);

				if (x + 1 < cubes.size()) neighbors.emplace_back(cubes[x + 1][y][z]);
				if (x - 1 >= 0) neighbors.emplace_back(cubes[x - 1][y][z]);
				if (z - 1 >= 0) neighbors.emplace_back(cubes[x][y][z - 1]);
				if (z + 1 < cubes[x][y].size()) neighbors.emplace_back(cubes[x][y][z + 1]);

				if (y - 1 >= 0) neighbors.emplace_back(cubes[x][y - 1][z]);

				if (y + 1 < cubes[x].size() && y - 1 >= 0) {
					std::shuffle(neighbors.begin() + 1, neighbors.end() - 1, g);
				}
				else if (y + 1 > cubes[x].size()) {
					std::shuffle(neighbors.begin(), neighbors.end() - 1, g);
				}
				else if (y - 1 < 0) {
					std::shuffle(neighbors.begin() + 1, neighbors.end(), g);
				}

				neighbor_map[cubes[x][y][z]] = neighbors;

			}
		}
	
}

void ThermoSim::checkActive(Logical_Cube* cube, std::vector<Logical_Cube*> neighbors)
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

