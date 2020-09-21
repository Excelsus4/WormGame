#include "stdafx.h"
#include "Fruit.h"

Fruit::Fruit(wstring shaderFile, D3DXVECTOR2 start)
{
	position = start;

	sprite = new Sprite(Textures + L"Bullets.png", shaderFile, 173, 112, 184, 123);
	sprite->Position(position);
}

Fruit::~Fruit()
{
	SAFE_DELETE(sprite);
}

void Fruit::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	sprite->Update(V, P);
}

void Fruit::Render()
{
	sprite->Render();
}
