#pragma once

static class Cubependium {
public:
	Cubependium();
	struct  LogicalCube {
		const float volume = 1000000.0f;
		const float density = 1.0f;
		const float mass = density * volume;
		const float conductivity = 10.0f;
		const float specific_heat = 1.0f;
		const float melting_point = 373.0f;
		const float boiling_point = 573.0f;
	} lc;
	struct GoldCube : LogicalCube {
		const float volume = 1000000.0f;
		const float density = 19.3f;
		const float mass = density * volume;
		const float conductivity = .129f;
		const float specific_heat = 314.0f;
		const float melting_point = 1064.0f + 273.0f;
		const float boiling_point = 2700.0f + 273.0f;
	} gc;
	struct IronCube : LogicalCube {
		const float volume = 1000000.0f;
		const float density = 7.9f;
		const float mass = density*volume;
		const float conductivity = .45f;
		const float specific_heat = 79.5f;
		const float melting_point = 1538.0f+273.0f;
		const float boiling_point = 2862.0f+273.0f;
	} ic;
	struct InsulatorCube : LogicalCube {
		const float volume = 1000000.0f;
		const float density = 19.3f;
		const float mass = density*volume;
		const float conductivity = 0.0f;
		const float specific_heat = 100.0f;
		const float melting_point = 10000.0f;
		const float boiling_point = 100000.0f;
	} inc;
	struct AirCube : LogicalCube {
		const float volume = 1000000.0f;
		const float density = .0013f;
		const float mass = density*volume;
		const float conductivity = .024f;
		const float specific_heat = 1.0f;
		const float melting_point = 0.0f;
		const float boiling_point = 0.0f;
	} ac;
	struct VacuumCube : LogicalCube {
		const float volume = 1000000.0f;
		const float density = 0;
		const float mass = 0;
		const float conductivity = 0;
		const float specific_heat = 0;
		const float melting_point = 0;
		const float boiling_point = 0;
	} vc;
	

	LogicalCube& getTypeData(size_t id) {
		switch (id) {
		case 0:
			return Cubependium::lc;
		case 1:
			return Cubependium::gc;
		case 2: 
			return Cubependium::ac;
		case 3:
			return Cubependium::ic;
		case 4:
			return Cubependium::inc;
		case 5: 
			return Cubependium::vc;
		}
	}


};