#pragma once
#include "ConstantBuffers.h"
#include "Drawable.h"


class TransformPSConstants : public Bindable
{
public:
	TransformPSConstants(Graphics& gfx, const Drawable& parent);
	void Bind(Graphics& gfx) noexcept override;
private:
	static std::unique_ptr<PixelConstantBuffer<PixelShaderConstants>> pPcbuf;
	const Drawable& parent;
};