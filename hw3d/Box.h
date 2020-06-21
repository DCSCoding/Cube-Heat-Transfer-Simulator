#pragma once
#include "DrawableBase.h"

class Box : public DrawableBase<Box>
{
public:
	Box( Graphics& gfx, float& xdis, float& ydis, float& zdis,
		float& temp1);
	void Update( float dt ) noexcept override;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;
private:
	// positional
	float x;
	float y;
	float z;;
	// model transform
	DirectX::XMFLOAT3X3 mt;
	//temp
	float& temp;
};