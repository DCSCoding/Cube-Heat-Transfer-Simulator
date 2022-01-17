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
	float pad3;
	float pad4;
};

StructuredBuffer<Cube> Buffer0 : register(t0);
RWStructuredBuffer<Cube> BufferOut : register(u0);

Cube updateCube(Cube c, float d_energy) {
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
	return c;
};

//512 threads. 8x8x8 is probably the optimal configuration for the 3d version of this, because it is divisible by 32/64.
[numthreads(8, 8, 8)]
void main(uint3 DTid : SV_DispatchThreadID)
{
	//Calculates temperature change for each neighbor. At the moment, this block of code references neighbors that might not exist.
	//For example, the first cube in the chunk only has 3 neighbors (x+1, y+1, z+1). HLSL seems to just ignore references to out of bounds indecies...
	//If this is the case, then there is no need to update. Should investigate. 

	//This is the 3d version of the shader. As a goal, it should be able to accept an arbitrary number of chunks (16,384), with undefined dimensions (it may be 1x1x1 or 3x10x7, who knows).
	float d_energy = 0;
	float transfer_rate = 0;

	//Calculate energy transfer to cube x + 1
	transfer_rate = (Buffer0[DTid.x][DTid.y][DTid.z].conductivity * Buffer0[DTid.x + 1][DTid.y][DTid.z].conductivity) * (Buffer0[DTid.x][DTid.y][DTid.z].temperature - Buffer0[DTid.x + 1][DTid.y][DTid.z].temperature);
	d_energy += transfer_rate;
	
	//Calculate energy transfer to cube x - 1
	transfer_rate = (Buffer0[DTid.x][DTid.y][DTid.z].conductivity * Buffer0[DTid.x + 1][DTid.y][DTid.z].conductivity) * (Buffer0[DTid.x][DTid.y][DTid.z].temperature - Buffer0[DTid.x - 1][DTid.y][DTid.z].temperature);
	d_energy += transfer_rate;
	
	//Calcuate energy transfer to cube y + 1
	transfer_rate = (Buffer0[DTid.x][DTid.y][DTid.z].conductivity * Buffer0[DTid.x][DTid.y + 1][DTid.z].conductivity) * (Buffer0[DTid.x][DTid.y][DTid.z].temperature - Buffer0[DTid.x][DTid.y + 1][DTid.z].temperature);
	d_energy += transfer_rate;
	
	//Calculate energy transfer to cube y - 1

	transfer_rate = (Buffer0[DTid.x][DTid.y][DTid.z].conductivity * Buffer0[DTid.x][DTid.y - 1][DTid.z].conductivity) * (Buffer0[DTid.x][DTid.y][DTid.z].temperature - Buffer0[DTid.x][DTid.y - 1][DTid.z].temperature);
	d_energy += transfer_rate;
	
	//Calculate energy transfer to cube z + 1
	transfer_rate = (Buffer0[DTid.x][DTid.y][DTid.z].conductivity * Buffer0[DTid.x][DTid.y][DTid.z + 1].conductivity) * (Buffer0[DTid.x][DTid.y][DTid.z].temperature - Buffer0[DTid.x][DTid.y][DTid.z + 1].temperature);
	d_energy += transfer_rate;

	//Calculate energy transfer to cube z - 1
	transfer_rate = (Buffer0[DTid.x][DTid.y][DTid.z].conductivity * Buffer0[DTid.x][DTid.y][DTid.z - 1].conductivity) * (Buffer0[DTid.x][DTid.y][DTid.z].temperature - Buffer0[DTid.x][DTid.y][DTid.z - 1].temperature);
	d_energy += transfer_rate;
	
	BufferOut[DTid.x][DTid.y][DTid.z] = updateCube(Buffer0[DTid.x][DTid.y][DTid.z], d_energy);
};