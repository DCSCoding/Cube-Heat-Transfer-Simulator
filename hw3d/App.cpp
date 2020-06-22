#include "App.h"
#include "Melon.h"
#include "Pyramid.h"
#include "Box.h"
#include <memory>
#include <algorithm>
#include "ChiliMath.h"
#include "ThermoSim.h"
#include <iostream>

ThermoSim ts(10, 10, 10);
App::App()
	:
	wnd( 1920, 1080,"Thermo" )
{
	class Factory
	{
	public:
		Factory( Graphics& gfx )
			:
			gfx( gfx )
		{}
		
		std::unique_ptr<Drawable> operator()()
		{
			/*switch( typedist( rng ) )
			{
			case 0:
				return std::make_unique<Pyramid>(
					gfx,rng,adist,ddist,
					odist,rdist
				);
			case 1:
				return std::make_unique<Box>(
					gfx,rng,adist,ddist,
					odist,rdist,bdist,ptemp
				);
			case 2:
				return std::make_unique<Melon>(
					gfx,rng,adist,ddist,
					odist,rdist,longdist,latdist
				);
			default:
				assert( false && "bad drawable type in factory" );
				return {};
			}*/
		}
	private:
		Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> typedist{ 0,2 };
	};

	
	Factory f( wnd.Gfx() );
	/*drawables.reserve( nDrawables );
	std::generate_n( std::back_inserter( drawables ),nDrawables,f );*/
	
	for (int x = 0; x < ts.width; x++) {
		for (int y = 0; y < ts.length; y++) {
			for (int z = 0; z < ts.height; z++) {
				float fx = float(x);
				float fy = float(y);
				float fz = float(z);
				drawables.push_back(std::make_unique<Box>(wnd.Gfx(), fx, fy, fz, ts, 0.0f, 0.0f, 0.0f));
			}
		}
	}

	wnd.Gfx().SetProjection( DirectX::XMMatrixPerspectiveLH( 1.0f,3.0f / 4.0f,0.5f,40.0f ) );
}

void App::DoFrame()
{
	std::cout << ts.height + ts.width + ts.length;
	ts.update(ts.cubes2);
	const auto dt = timer.Mark();
	wnd.Gfx().ClearBuffer( 0.07f,0.0f,0.12f );
	for( auto& d : drawables )
	{
		d->Update( dt );
		d->Draw( wnd.Gfx() );
	}

	wnd.Gfx().EndFrame();
	
}

App::~App()
{}


int App::Go()
{
	
	while( true )
	{
		// process all messages pending, but to not block for new messages
		if( const auto ecode = Window::ProcessMessages() )
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}