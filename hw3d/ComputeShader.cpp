#include "ComputeShader.h"

ComputeShader::ComputeShader(Graphics& gfx, const std::wstring& path, ID3D11ShaderResourceView* pSourceBufferView, ID3D11UnorderedAccessView* pDestBufferView) : 
	m_srcDataGPUBufferView(pSourceBufferView), 
	m_destDataGPUBufferView(pDestBufferView)
{
	INFOMAN(gfx);
	
	
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	
	GFX_THROW_INFO(D3DReadFileToBlob(path.c_str(), &pBlob));

	GFX_THROW_INFO(gfx.getDevice()->CreateComputeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pComputeShader));
	
	gfx.getContext()->CSSetShader(pComputeShader.Get(), nullptr, 0u);
	gfx.getContext()->CSSetShaderResources(0, 1, &m_srcDataGPUBufferView);
	gfx.getContext()->CSSetUnorderedAccessViews(0, 1, &m_destDataGPUBufferView, NULL);

}

void ComputeShader::run(Graphics& gfx, int chunks_width) {

	ID3D11UnorderedAccessView* ppUAViewNULL[1] = { NULL };
	ID3D11ShaderResourceView* ppSRVNULL[2] = { NULL, NULL };
	
	//2x2x2 at the moment because I'm doing one chunk. 
	//2x2x2 * 8x8x8 = 4096 
	gfx.getContext()->Dispatch(pow(chunks_width, 3)*4, 1, 1);

	gfx.getContext()->CSSetShader(NULL, NULL, 0);
	gfx.getContext()->CSSetUnorderedAccessViews(0, 1, ppUAViewNULL, NULL);
	gfx.getContext()->CSSetShaderResources(0, 2, ppSRVNULL);
}


void ComputeShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->CSSetShader(pComputeShader.Get(), nullptr, 0u);
}