#include "TransformPSConstants.h"

TransformPSConstants::TransformPSConstants(Graphics& gfx, const Drawable& parent) :
	parent(parent)
{
	if (!pPcbuf)
	{
		pPcbuf = std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx);
	}
}

void TransformPSConstants::Bind(Graphics& gfx) noexcept
{
	pPcbuf->Update(gfx, parent.GetPixelShaderConstants());
	pPcbuf->Bind(gfx);
}

std::unique_ptr<PixelConstantBuffer<PixelShaderConstants>> TransformPSConstants::pPcbuf;