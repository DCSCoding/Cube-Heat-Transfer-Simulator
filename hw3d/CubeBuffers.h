#pragma once
#include "Graphics.h"
#include "CubeData.h"

class CubeBuffers {
public:
	CubeBuffers();
	bool createInputBuffer(Graphics& gfx, CubeData cubes[], int array_size);
	bool createOutputBuffer(Graphics& gfx, CubeData cubes[], int array_size);
	void getResults(Graphics& gfx, CubeData destination[], int array_size);
	//static bool loadComputeShader(LPCWSTR filename, ID3D11ComputeShader** computeShader, Graphics& gfx);
	ID3D11ShaderResourceView* m_srcDataGPUBufferView;
	ID3D11UnorderedAccessView* m_destDataGPUBufferView;
	ID3D11Buffer* m_srcDataGPUBuffer;
	ID3D11Buffer* m_destDataGPUBuffer;
};