#pragma once
#include "DrawableBase.h"
#include "ThermoSim.h"
#include "PixelShaderConstants.h"

class WaterBox : public DrawableBase<WaterBox>
{
public:
	WaterBox(Graphics& gfx, size_t type, float xdis, float ydis, float zdis,
		ThermoSim& rts, float chi, float theta, float phi);
	void Update(float dt) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
	PixelShaderConstants GetPixelShaderConstants() const noexcept override;
	size_t box_type;
private:
	// positional
	float x;
	float y;
	float z;
	float chi;
	float theta;
	float phi;
	// model transform
	DirectX::XMFLOAT3X3 mt;
	//ThermoSim reference
	ThermoSim& ts;
};