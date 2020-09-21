#include "stdafx.h"
#include "./Systems/Device.h"
#include "./Objects/Worm.h"
#include "./Objects/Fruit.h"

Worm* character;
vector<Fruit*> fruits;

void InitScene() {
	wstring shaderFile = Shaders + L"008_Sprite.fx";

	character = new Worm(shaderFile, D3DXVECTOR2(Width / 2, Height/2), 15, 0.04f, 12);
	fruits.push_back(new Fruit(shaderFile, D3DXVECTOR2(100, 100)));
}

void DestroyScene(){
	SAFE_DELETE(character);
}

D3DXMATRIX V, P;
float cooltime = 5.0f;
float timer = 0.0f;

void Update() {
	timer += Timer->Elapsed();
	if (timer >= cooltime) {
		fruits.push_back(new Fruit(Shaders + L"008_Sprite.fx",
			D3DXVECTOR2(Math::Random(0, Width), Math::Random(0, Height))));
		timer = 0.0f;
	}


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

	for (auto a : fruits){
		a->Update(V, P);
	}
	character->Update(V, P);

	for (auto iter = fruits.begin(); iter != fruits.end();) {
		if (character->CollisionCheck((*iter)->Position(), 15.0f)) {
			iter = fruits.erase(iter);
			character->Grow(5);
		}
		else
			++iter;
	}
}

void Render() {
	D3DXCOLOR bgColor = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		for (auto a : fruits)
			a->Render();
		character->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}