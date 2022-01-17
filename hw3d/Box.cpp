#include "Box.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Cube.h"
#include "ThermoSim.h"
#include "CubeData.h"

Box::Box(Graphics& gfx, size_t type, float xdis, float ydis, float zdis,
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
			const PixelShaderConstants cb2 =
			{
				{
					{ 0, 0, 0 },
					{ 0, 0, 0 },
					{ 0, 0, 0 },
					{ 0, 0, 0 },
					{ 0, 0, 0 },
					{ 0, 0, 0 },
					{ 0, 0, 0 },
					{ 0, 0, 0 },
				}
			};
			AddStaticBind(std::make_unique<PixelConstantBuffer<PixelShaderConstants>>(gfx, cb2));

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

	AddBind(std::make_unique<TransformCbuf>(gfx, *this));

	// model deformation transform (per instance, not stored as bind)
	dx::XMStoreFloat3x3(
		&mt,
		dx::XMMatrixScaling(1.0f, 1.0f, 1.0f)
	);
}

void Box::Update( float dt ) noexcept
{

	theta += 1.0f * dt;
	phi += 1.0f * dt;
	chi += 1.0f * dt;
}

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMLoadFloat3x3(&mt) *
		//dx::XMMatrixRotationRollPitchYaw(theta, phi, chi)*
		dx::XMMatrixTranslation(x, y, z);
		//dx::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}

PixelShaderConstants Box::GetPixelShaderConstants() const noexcept {
	
	float temp = pcd->temperature / 1000.0f;
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