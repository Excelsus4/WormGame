#pragma once

class Worm {
public:
	Worm(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed, int length);
	~Worm();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Reflection(const D3DXVECTOR2& n);
	void VectorRotate(const float& angle);

	bool CollisionCheck(const D3DXVECTOR2& pos, const float& colSize);
	void Grow(int amount);
private:
	int length;

	float cooltime;
	float timer;

	D3DXVECTOR2 velocity;
	D3DXVECTOR2 position;

	Sprite* Head;
	vector<Sprite*> body;
};