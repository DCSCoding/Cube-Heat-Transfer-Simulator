#include "WaterBox.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Cube.h"
#include "ThermoSim.h"
#include "CubeData.h"


WaterBox::WaterBox(Graphics& gfx, size_t type, float xdis, float ydis, float zdis,
	Logical_Cube* pcube, float chi1, float theta1, float phi1, CubeData* pCubeData)
	:
	box_type(type),
	x(xdis),
	y(ydis),
	z(zdis),
	pc(pcube),
	chi(chi1),
	theta(theta1),
	phi(phi1),
	pcd(pCubeData)

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

	
	float temperature = pcd->temperature;
	float temp = 0;
	if (temperature < 323) {
		temp = 0;
	}
	else {
		temp = (temperature / 1000 - .323) + (.02 * (temperature - 323));
	}
	
	const PixelShaderConstants cb2 =
	{
		{
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
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

void WaterBox::Update(float dt) noexcept
{

	theta += 1.0f * dt;
	phi += 1.0f * dt;
	chi += 1.0f * dt;
}

DirectX::XMMATRIX WaterBox::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMLoadFloat3x3(&mt) *
		//dx::XMMatrixRotationRollPitchYaw(theta, phi, chi)*
		dx::XMMatrixTranslation(x, y, z);
	//dx::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}

PixelShaderConstants WaterBox::GetPixelShaderConstants() const noexcept {
	float temperature = pcd->temperature;
	float temp = 0;
	if (temperature < 323) {
		temp = 0;
	}
	else {
		temp = (temperature/1000 -.323) + (.02*(temperature-323));
	}
	const PixelShaderConstants cb2 =
	{
		{
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
			{ temp,temp,1 },
		}
	};
	return cb2;
}