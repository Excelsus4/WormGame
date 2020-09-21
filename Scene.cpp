#include "stdafx.h"
#include "./Systems/Device.h"
#include "./Objects/Worm.h"

Worm* character;

void InitScene() {
	wstring spriteFile = Textures + L"Metalslug.png";
	wstring shaderFile = Shaders + L"008_Sprite.fx";

	character = new Worm(shaderFile, D3DXVECTOR2(Width / 2, Height/2), 15, 0.15f, 12);
}

void DestroyScene(){
	SAFE_DELETE(character);
}

D3DXMATRIX V, P;

void Update() {
	//============================================================================
	// Player Key Input
	if (Key->Press(VK_RIGHT))
		character->VectorRotate(Math::ToRadian(-0.05f));
	if (Key->Press(VK_LEFT))
		character->VectorRotate(Math::ToRadian(0.05f));

	//View
	D3DXVECTOR3 eye(0, 0, -1);
	D3DXVECTOR3 at(0, 0, 0);
	D3DXVECTOR3 up(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &at, &up);

	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);

	character->Update(V, P);
}

void Render() {
	D3DXCOLOR bgColor = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		character->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}