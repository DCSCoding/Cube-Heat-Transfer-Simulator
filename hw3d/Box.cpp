#include "Box.h"
#include "BindableBase.h"
#include "GraphicsThrowMacros.h"
#include "Cube.h"
#include "ThermoSim.h"


Box::Box( Graphics& gfx, float xdis, float ydis, float zdis,
	ThermoSim& rts)
	:
	x(xdis),
	y(ydis),
	z(zdis),
	ts(rts)
{
	namespace dx = DirectX;

	if( !IsStaticInitialized() )
	{
		struct Vertex
		{
			dx::XMFLOAT3 pos;
		};
		const auto model = Cube::Make<Vertex>();

		AddStaticBind( std::make_unique<VertexBuffer>( gfx,model.vertices ) );

		auto pvs = std::make_unique<VertexShader>( gfx,L"ColorIndexVS.cso" );
		auto pvsbc = pvs->GetBytecode();
		AddStaticBind( std::move( pvs ) );

		AddStaticIndexBuffer( std::make_unique<IndexBuffer>( gfx,model.indices ) );

		AddStaticBind(std::make_unique<PixelShader>(gfx, L"ColorIndexPS.cso"));

		/*struct PixelShaderConstants
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
				{ temp/1000.0f,temp/1000.0f,temp/1000.0f },
				{ temp/1000.0f,temp/1000.0f,temp/1000.0f },
				{ temp/1000.0f,temp/1000.0f,temp/1000.0f },
				{ temp/1000.0f,temp/1000.0f,temp/1000.0f },
				{ temp/1000.0f,temp/1000.0f,temp/1000.0f },
				{ temp/1000.0f,temp/1000.0f,temp/1000.0f },
				{ temp/1000.0f,temp/1000.0f,temp/1000.0f },
				{ temp/1000.0f,temp/1000.0f,temp/1000.0f },
			}
		};
		AddStaticBind( std::make_unique<PixelConstantBuffer<PixelShaderConstants>>( gfx,cb2 ) );*/

		const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
		{
			{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		};
		AddStaticBind( std::make_unique<InputLayout>( gfx,ied,pvsbc ) );

		AddStaticBind( std::make_unique<Topology>( gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
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


	float temp = ts.cubes[x][y][z].getTemperature() / 1000.0f;
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

	AddBind( std::make_unique<TransformCbuf>( gfx,*this ) );
	
	// model deformation transform (per instance, not stored as bind)
	dx::XMStoreFloat3x3(
		&mt,
		dx::XMMatrixScaling( 0.5f,0.5f,0.5f )
	);
}

void Box::Update( float dt ) noexcept
{
	
	/*roll += droll * dt;
	pitch += dpitch * dt;
	yaw += dyaw * dt;
	theta += dtheta * dt;
	phi += dphi * dt;
	chi += dchi * dt;*/
}

DirectX::XMMATRIX Box::GetTransformXM() const noexcept
{
	namespace dx = DirectX;
	return dx::XMLoadFloat3x3( &mt ) *
		dx::XMMatrixRotationRollPitchYaw(0.0, 0.0f, 0.0f)*
		dx::XMMatrixTranslation( x,y,z) *
		dx::XMMatrixTranslation( -4.5f,-4.5f,10.0f );
}

PixelShaderConstants Box::GetPixelShaderConstants() const noexcept {
	
	float temp = ts.cubes[x][y][z].getTemperature() / 1000.0f;
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