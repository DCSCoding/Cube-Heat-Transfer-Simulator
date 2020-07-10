#include "App.h"
#include "NonStaticBox.h"
#include "GoldBox.h"
#include "IronBox.h"
#include "WaterBox.h"
#include "Melon.h"
#include "Pyramid.h"
#include "Box.h"
#include "Sheet.h"
#include "SkinnedBox.h"
#include <memory>
#include <algorithm>
#include "ChiliMath.h"
#include "Surface.h"
#include "GDIPlusManager.h"
#include "ThermoSim.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "Chunk.h"
#include <future>

ThermoSim ts;
long duration = 0;
float average = 0;

App::App()
	:
	wnd(1920, 1080, "Thermo")
{
	class Factory
	{
	public:
		Factory(Graphics& gfx)
			:
			gfx(gfx)
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

	Factory f(wnd.Gfx());
	for (int i = 0; i < 2; i++) {
		ts.addChunk(0, i, 0);
	}
	
	
	//ts.addChunk(0, 0, 1B
	/*drawables.reserve( nDrawables );
	std::generate_n( std::back_inserter( drawables ),nDrawables,f );*/

	for (Chunk c : ts.chunks) {
		for (Logical_Cube* cube : c.pcubes) {
			size_t id = cube->getType();
			int offx = (c.x_pos) * 16;
			int offy = (c.y_pos) * 16;
			int offz = (c.z_pos) * 16;
			float x = int((cube->getIndex() / 256)) + offx;
			float y = int(((cube->getIndex() / 16) % 16)) + offy;
			float z = int(((cube->getIndex() % 16))) + offz;
			

			switch (id) {
			case 1:
				drawables.emplace_back(std::make_unique<GoldBox>(wnd.Gfx(), id, x, y, z, cube, 0.0f, 0.0f, 0.0f));
				break;
			case 2:
				drawables.emplace_back(std::make_unique<IronBox>(wnd.Gfx(), id, x, y, z, cube, 0.0f, 0.0f, 0.0f));
				break;
			case 3:
				//drawables.push_back(std::make_unique<InsulatorBox>(wnd.Gfx(), id, x, y, z, cube, 0.0f, 0.0f, 0.0f));
				break;
			case 4:
				//drawables.push_back(std::make_unique<NonStaticBox>(wnd.Gfx(), id, x, y, z, cube, 0.0f, 0.0f, 0.0f));
				break;
			case 6:
				drawables.emplace_back(std::make_unique<WaterBox>(wnd.Gfx(), id, x, y, z, cube, 0.0f, 0.0f, 0.0f));
			}
		}
	}
	/*for (int x = 0; x < ts.width; x++) {
		for (int y = 0; y < ts.length; y++) {
			for (int z = 0; z < ts.height; z++) {
				float fx = float(x);
				float fy = float(y);
				float fz = float(z);

				size_t id = ts.cubes2[x][y][z]->getType();
				
				switch (id) {
				case 1 :
					drawables.push_back(std::make_unique<GoldBox>(wnd.Gfx(), id, fx, fy, fz, ts, 0.0f, 0.0f, 0.0f));
					break;
				case 2:
					drawables.push_back(std::make_unique<IronBox>(wnd.Gfx(), id, fx, fy, fz, ts, 0.0f, 0.0f, 0.0f));
					break;
				case 3:
					drawables.push_back(std::make_unique<InsulatorBox>(wnd.Gfx(), id, fx, fy, fz, ts, 0.0f, 0.0f, 0.0f));
					break;
				case 4:
					drawables.push_back(std::make_unique<NonStaticBox>(wnd.Gfx(), id, fx, fy, fz, ts, 0.0f, 0.0f, 0.0f));
					break;
				case 6:
					drawables.push_back(std::make_unique<WaterBox>(wnd.Gfx(), id, fx, fy, fz, ts, 0.0f, 0.0f, 0.0f));
				}
				
			}
		}
	}*/

	// auto s = Surface::FromFile("Images\kappa50.png");

	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 80.0f));
	
}

void App::DoFrame(size_t framecount)
{
	
	const auto dt = timer.Mark();

	if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
		wnd.Gfx().DisableImgui();
	}
	else {
		wnd.Gfx().EnableImgui();
	}

	
	
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(cam.GetMatrix());
	for (auto& d : drawables)
	{
		d->Update(dt);
		d->Draw(wnd.Gfx());
	}

	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	
	cam.SpawnControlWindow();
	CubeMenu();
	//present
	wnd.Gfx().EndFrame();

}

App::~App()
{}


int App::Go()
{
	std::random_device rg;
	std::mt19937 g(rg());
	size_t framecount = 0;
	int steps[64];
	for (int k = 0; k < 64; k++) {
		steps[k] = k;
	}
	std::shuffle(&steps[0], &steps[64], rg);
	std::vector<std::future<void>> update_futures;
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame(framecount);
		
		
		framecount++;
		if (framecount == 63) {
			if (update_futures.size() > 1) {
				for (auto& f : update_futures) {
					f.wait();
				}
			}
			
			ts.update_neighbor_chunks();
			auto t1 = std::chrono::high_resolution_clock::now();
			for (int chunk_index = 0; chunk_index < ts.chunks.size(); chunk_index++) {
				//update_futures.push_back(std::async(std::launch::async, &ThermoSim::update, &ts, steps[framecount], chunk_index));
				update_futures.push_back(std::async(std::launch::async, &ThermoSim::update_all, &ts, chunk_index));
			}
			auto t2 = std::chrono::high_resolution_clock::now();
			duration += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			average = duration / 64;
			duration = 0;
			framecount = 0;
			std::shuffle(&steps[0], &steps[64], rg);
		}
	}
}

void App::CubeMenu() {
	
	if (ImGui::Begin("Cube Menu"))
	{
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("%.1f microseconds per cycle", average);
		/*for (int x = 0; x < ts.cubes.size(); x++) {
			for (int y = 0; y < ts.cubes[x].size(); y++) {
				for (int z = 0; z < ts.cubes[x][y].size(); z++) {
					if(ts.cubes[x][y][z].getType() != 3)
					ImGui::Text("Temperature: %.3f %u %i %i %i id: %i", pc->getTemperature(), ts.cubes[x][y][z].isActive(), x, y, z, int(ts.cubes[x][y][z].getType()));
				}
			}
		}*/
		/*for (Chunk c : ts.chunks) {
			for (Logical_Cube* cube : c.pcubes) {
				if (cube->getType() != 3) {
					ImGui::Text("Temperature: %.3f %u %h id: %i", cube->getTemperature(), cube->isActive(), cube->getIndex(), int(cube->getType()));
				}
			}
		}*/

		for (int i = 0; i < ts.chunks.size(); i++) {
			for (int m = 0; m < 10; m++) {
				if (ts.chunks[i].pcubes[m]->getType() != 3) {
					ImGui::Text("Temperature: %.3f %u %h id: %i", ts.chunks[i].pcubes[m]->getTemperature(), ts.chunks[i].pcubes[m]->isActive(), ts.chunks[i].pcubes[m]->getIndex(), int(ts.chunks[i].pcubes[m]->getType()));
				}
			}
		}
		
	};
	ImGui::End();
}