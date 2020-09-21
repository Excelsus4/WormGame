#pragma once

class Fruit {
public:
	Fruit(wstring shaderFile, D3DXVECTOR2 start);
	~Fruit();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	D3DXVECTOR2 Position() const { return position; }

private:
	D3DXVECTOR2 position;

	Sprite* sprite;
};