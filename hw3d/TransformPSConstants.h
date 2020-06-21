#pragma once
#include "PixelShaderConstants.h"
#include "Drawable.h"
#include "ConstantBuffers.h"

class TransformPSConstants : public Bindable
{
public:
	TransformPSConstants(Graphics& gfx, const Drawable& parent);
	void Bind(Graphics& gfx) noexcept override;
private:
	static std::unique_ptr<PixelConstantBuffer<PixelShaderConstants>> pPcbuf;
	const Drawable& parent;
};