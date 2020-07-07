#include "NonStaticBox.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Cube.h"
#include "ThermoSim.h"


NonStaticBox::NonStaticBox(Graphics& gfx, size_t type, float xdis, float ydis, float zdis,
	Logical_Cube* pcube, float chi1, float theta1, float phi1)
	:
	box_type(type),
	x(xdis),
	y(ydis),
	z(zdis),
	pc(pcube),
	chi(chi1),
	theta(theta1),
	phi(phi1)

{
	namespace dx = DirectX;

	if (!IsStaticInitialized())
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
		};
		const auto model = Cube::Make<Vertex>();

		AddStaticBind(std::make_unique<VertexBuffer>(gfx, model.vertices));

		auto pvs = std::make_unique<VertexShader>(gfx, L"ColorIndexVS.cso");
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind(std::move(pvs));

		AddStaticIndexBuffer(std::make_unique<IndexBuffer>(gfx, model.indices));

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"ColorIndexPS.cso"));

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind(std::make_unique<InputLayout>(gfx, ied, pvsbc));

		AddStaticBind(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	else
	{
		SetIndexFromStatic();
	}

	struct PixelShaderConstants
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[8];
	};


	float temp = pc->getTemperature() / 1000.0f;
	
	const PixelShaderConstants cb2 =
	{
		{
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
		}
	};
	AddBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx, cb2));

	AddBind(std::make_unique<TransformPSConstants>(gfx, *this));



	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

	// model deformation transform (per instance, not stored as bind)
	dx::XMStoreFloat3x3(
		&mt,
		dx::XMMatrixScaling(1.0f, 1.0f, 1.0f)
	);
}

void NonStaticBox::Update(float dt) noexcept
{

	theta += 1.0f * dt;
	phi += 1.0f * dt;
	chi += 1.0f * dt;
}

DirectX::XMMATRIX NonStaticBox::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMLoadFloat3x3(&mt) *
		//dx::XMMatrixRotationRollPitchYaw(theta, phi, chi)*
		dx::XMMatrixTranslation(x, y, z);
	//dx::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}

PixelShaderConstants NonStaticBox::GetPixelShaderConstants() const noexcept {

	float temp = pc->getTemperature() / 1000.0f;
	const PixelShaderConstants cb2 =
	{
		{
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
			{ temp,temp,temp },
		}
	};
	return cb2;
}