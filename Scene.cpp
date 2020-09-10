#include "stdafx.h"
#include "Device.h"
#include "Player.h"

Player* player;

void InitScene() {
	player = new Player(L"../_Shaders/006_Rect.fx");
	player->Scale(100, 100);

	float x = (float)Width*0.5f - player->Scale().x * 0.5f;
	float y = player->Scale().y * 0.5f;
	player->Position(x, y);
}

void DestroyScene() {
	SAFE_DELETE(player);
}

D3DXMATRIX V, P;
bool bIsMoving = false;
float speed = 200.0f;
float js = 0.6f;

void Update() {
	//Replace this with a auto movement, which needs a stopper at either end
	if (bIsMoving)
		player->AutoMove();

	if (Key->Down(VK_SPACE))
		player->StartJump();
	else if (Key->Up(VK_SPACE))
		player->EndJump();

	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	player->ViewProjection(V, P);

	player->Update();
}

void Render() {
	D3DXCOLOR bgColor = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		//Create ImGUI Slider Float for adjusting speed, Create ImGUI Button For Start and Stop
		if (ImGui::Button(bIsMoving?"Stop":"Start")) {
			bIsMoving = !bIsMoving;
		}
		speed = player->Speed();
		ImGui::SliderFloat("Speed", &speed, 0.0f, 400.0f);
		player->Speed(speed);

		js = player->Strength();
		ImGui::SliderFloat("Strength", &js, 0.0f, 1.0f);
		player->Strength(js);

		player->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}