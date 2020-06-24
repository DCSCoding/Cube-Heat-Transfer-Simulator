#include "Camera.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	const auto pos = dx::XMVector3Transform(
		dx::XMVectorSet( x , y , -z, 0.0f ),
		dx::XMMatrixRotationRollPitchYaw( phi,-theta, 0.0f )
	);
	return dx::XMMatrixLookAtLH(
		pos,dx::XMVectorZero(),
		dx::XMVectorSet( 0.0f,1.0f,0.0f,0.0f )
	) * dx::XMMatrixRotationRollPitchYaw(
		pitch,-yaw,roll
	);
}

void Camera::SpawnControlWindow() noexcept
{
	if (ImGui::Begin("Camera"))
	{
		if (ImGui::CollapsingHeader("Camera Controls")){
			ImGui::Text("Position");
			ImGui::SliderFloat("X", &x, 0.0f, 80.0f, "%.1f");
			ImGui::SliderFloat("Y", &y, 0.0f, 80.0f, "%.1f");
			ImGui::SliderFloat("Z", &z, 0.0f, 80.0f, "%.1f");
			ImGui::SliderAngle("Theta", &theta, -180.0f, 180.0f);
			ImGui::SliderAngle("Phi", &phi, -89.0f, 89.0f);
			ImGui::Text("Orientation");
			ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
			ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
			ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	}
	ImGui::End();
}

void Camera::Reset() noexcept
{
	x = 0.0f;
	y = 0.0f;
	z = 20.0f;
	theta = 0.0f;
	phi = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
}

void Camera::Move(char c) {
	switch (c) {
	case 'w':
		z += 1.0f / 20.0f;
	case 'a':
		x -= 1.0f / 20.0f;
	case 's':
		z -= 1.0f / 20.0f;
	case 'd':
		x += 1.0f / 20.0f;
	case 'q':
		y -= 1.0f / 20.0f;
	case 'e':
		y += 1.0f / 20.0f;
	}
	
		
}
