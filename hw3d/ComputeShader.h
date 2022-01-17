#pragma once
#include "Bindable.h"
#include "ConstantBuffers.h"
class ComputeShader : public Bindable
{
public:
	ComputeShader(Graphics& gfx, const std::wstring& path, ID3D11ShaderResourceView* pSourceBufferView, ID3D11UnorderedAccessView* pDestBufferView);
	void run(Graphics& gfx, int chunks_width);
	void Bind(Graphics& gfx) noexcept override;
	ID3D11ShaderResourceView* m_srcDataGPUBufferView;
	ID3D11UnorderedAccessView* m_destDataGPUBufferView;
protected:
	Microsoft::WRL::ComPtr<ID3D11ComputeShader> pComputeShader;

};