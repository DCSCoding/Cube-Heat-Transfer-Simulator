//1 chunk is 262,144 bytes... 1000 chunks is 262,144,000 MB. Still well within parameters, but it might be useful to reduce this size.
//Half precision floats? Removing the padding? (could hurt performance by having cache misses, might not be that important)
struct Cube
{
	float temperature;
	float energy_content;
	float volume;
	float density;
	float mass;
	float mass_specific_heat;
	float conductivity;
	float specific_heat;
	float melting_point;
	float boiling_point;
	int state;
	float x_pos;
	float y_pos;
	float z_pos;
	float x_interval;
	float y_interval;
};

StructuredBuffer<Cube> Buffer0 : register(t0);
RWStructuredBuffer<Cube> BufferOut : register(u0);

//This created 2 new cubes, so is probably quite wasteful. 
/*Cube updateCube(Cube c, Cube up_neighbor, Cube down_neighbor, float d_energy) {
	c.energy_content -= d_energy;
	c.temperature = c.energy_content / c.mass_specific_heat;
	if (c.temperature < c.melting_point) {
		c.state = 0;
	}
	else if (c.temperature > c.boiling_point) {
		c.state = 2;
	}
	else {
		c.state = 1;
	}
	//convection, no state check
	if (c.temperature > up_neighbor.temperature) {
		c = up_neighbor;
	}
	else if (c.temperature < down_neighbor.temperature) {
		c = down_neighbor;
	}
	
	return c;
};*/

//1024 threads (1 dimensional). At the moment threads are distributed 1-dimensionally. As far as I know, this shouldn't be any slower than a 3 dimensional distribution.
//1024 threads is the maximum number permitted by Shader Model 5. Each shader call will distribute a number of work groups = 4 * the number of chunks. 

[numthreads(1024, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
	//Calculates temperature change for each neighbor. At the moment, this block of code references neighbors that might not exist.
	//For example, the first cube in the chunk only has 3 neighbors (x+1, y+1, z+1). HLSL seems to just ignore references to out of bounds indecies...
	//If this is the case, then there is no need to update. Should investigate. 

	//Believe it or not, referencing thread 1023 + 256 actually works. It will look for this thread in the next workgroup over. 
	float d_energy = 0;
	float transfer_rate = 0;
	int x_interval = Buffer0[DTid.x].x_interval;
	int y_interval = Buffer0[DTid.y].y_interval;

	//Unless it's the first cube (id = 0), if the cube's id divides evenly into the y_interval-1, it is not adjacent to the cube at id + 1.
	if (DTid.x == 0 || DTid.x % Buffer0[DTid.x].y_interval-1 != 0) {
		transfer_rate = (Buffer0[DTid.x].conductivity * Buffer0[DTid.x + 1].conductivity) * (Buffer0[DTid.x].temperature - Buffer0[DTid.x + 1].temperature);
		d_energy += transfer_rate;
	}
	//If the cube's id divides evenly into the y_interval, then it is not adjacent to the cube at id - 1.
	if (DTid.x % Buffer0[DTid.x].y_interval != 0) {
		transfer_rate = (Buffer0[DTid.x].conductivity * Buffer0[DTid.x - 1].conductivity) * (Buffer0[DTid.x].temperature - Buffer0[DTid.x - 1].temperature);
		d_energy += transfer_rate;
	}
	//If the cube has a y position equal to the y_interval - 1, then it is not adjacent to the cube at id at +1 y_interval.
	if (Buffer0[DTid.x].y_pos != Buffer0[DTid.x].y_interval - 1) {
		transfer_rate = (Buffer0[DTid.x].conductivity * Buffer0[DTid.x + Buffer0[DTid.x].y_interval].conductivity) * (Buffer0[DTid.x].temperature - Buffer0[DTid.x + Buffer0[DTid.x].y_interval].temperature);
		d_energy += transfer_rate;
	}
	//If the cube has a y position of 0, then it is not adjacent to the cube at id - 1 y_interval.
	if (Buffer0[DTid.x].y_pos != 0) {
		transfer_rate = (Buffer0[DTid.x].conductivity * Buffer0[DTid.x - Buffer0[DTid.x].y_interval].conductivity) * (Buffer0[DTid.x].temperature - Buffer0[DTid.x - Buffer0[DTid.x].y_interval].temperature);
		d_energy += transfer_rate;
	}
	//The only time a cube isn't adjacent to the cube at +256 or -256 is when that cube doesn't exist, so we can avoid this check (I think).
	transfer_rate = (Buffer0[DTid.x].conductivity * Buffer0[DTid.x + Buffer0[DTid.x].x_interval].conductivity) * (Buffer0[DTid.x].temperature - Buffer0[DTid.x + Buffer0[DTid.x].x_interval].temperature);
	d_energy += transfer_rate;
	transfer_rate = (Buffer0[DTid.x].conductivity * Buffer0[DTid.x - Buffer0[DTid.x].x_interval].conductivity) * (Buffer0[DTid.x].temperature - Buffer0[DTid.x - Buffer0[DTid.x].x_interval].temperature);
	d_energy += transfer_rate;

	Cube temp = Buffer0[DTid.x];

	temp.energy_content -= d_energy;
	temp.temperature = temp.energy_content / temp.mass_specific_heat;
	
	if (temp.temperature < temp.melting_point) {
		temp.state = 0;
	}
	else if (temp.temperature > temp.boiling_point) {
		temp.state = 2;
	}
	else {
		temp.state = 1;
	}
	
	//convection, no state check
	/*if (temp.temperature > Buffer0[DTid.x + y_interval].temperature) {
		temp = Buffer0[DTid.x + y_interval];
	}
	
	else if (temp.temperature < Buffer0[DTid.x - y_interval].temperature) {
		temp = Buffer0[DTid.x - y_interval];
	}*/

	BufferOut[DTid.x] = temp;

};