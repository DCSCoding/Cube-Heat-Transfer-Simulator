#pragma once

class Cubependium {
public:
	Cubependium();
	struct Cube_Data {
		 size_t type_id;
		 float volume;
		 float density;
		 float mass = density * volume;
		 float conductivity;
		 float specific_heat;
		 float melting_point;
		 float boiling_point;
	};
	Cube_Data lc = {
		 1,
		 1000000.0f,
		 1.0f,
		 1000000.0f * 1.0f,
		 100.0f,
		 1.0f,
		 1000.0f,
		 2700.0f + 273.0f
	};
	Cube_Data gc = {
		 1,
		 1000000.0f,
		 19.3f,
		 1000000.0f * 19.3,
		 314.0f,
		 .129,
		 1064.0f + 273.0f,
		 2700.0f + 273.0f
	};
	Cube_Data ic{
		 2,
		 1000000.0f,
		 7.9f,
		 1000000.0f * 7.9f,
		 79.5f,
		 .45f,
		 1538.0f + 273.0f,
		 2862.0f + 273.0f
	};
	Cube_Data inc{
		 3,
		 1000000.0f,
		 19.3f,
		 1000000.0f * 19.3,
		 0.0f,
		 100.0f,
		 10000.0f,
		 100000.0f
	};
	Cube_Data ac{
		 4,
		 1000000.0f,
		 .0013f,
		 1000000.0f * .0013,
		 .024f,
		 1.0f,
		 0.0f,
		 0.0f
	};
	Cube_Data vc{
		 5,
		 1000000.0f,
		 0,
		 0,
		 0,
		 0,
		 0,
		 0
	};
	

	Cube_Data& getTypeData(size_t id){

		switch (id) {
		case 0:
			return Cubependium::lc;
			break;
		case 1:
			return Cubependium::gc;
			break;
		case 2: 
			return Cubependium::inc;
			break;
		case 3:
			return Cubependium::ic;
			break;
		case 4:
			return Cubependium::ac;
			break;
		case 5: 
			return Cubependium::vc;
			break;
		default: 
			return Cubependium::gc;
		}
	}

};