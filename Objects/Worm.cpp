#include "stdafx.h"
#include "Worm.h"

Worm::Worm(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed, int length)
{
	Sprite* cider;
	position = start;

	Head = new Sprite(Textures + L"Bullets.png", shaderFile, 252, 325, 270, 343);
	for (int i = 1; i < length; i++) {
		cider = new Sprite(Textures + L"Bullets.png", shaderFile, 252, 325, 270, 343);
		body.push_back(cider);
		cider->Position(position);
	}

	float radian = Math::ToRadian(angle);
	velocity.x = cosf(radian);
	velocity.y = sinf(radian);
	velocity *= speed;

	cooltime = 0.07f;
	timer = 0;
}

Worm::~Worm()
{
	SAFE_DELETE(Head);
	for (auto a : body)
		SAFE_DELETE(a);
}

void Worm::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (position.x < 0)
		Reflection(D3DXVECTOR2(1, 0));
	if (position.x > Width)
		Reflection(D3DXVECTOR2(-1, 0));
	if (position.y < 0)
		Reflection(D3DXVECTOR2(0, 1));
	if (position.y > Height)
		Reflection(D3DXVECTOR2(0, -1));

	Sprite* one = *(body.begin());

	timer += Timer->Elapsed();
	if (timer >= cooltime) {
		one->Position(position);
		body.erase(body.begin());
		body.push_back(one);

		timer = 0;
	}
	position += velocity;

	Head->Position(position);
	Head->Update(V, P);
	for (auto a : body)
		a->Update(V, P);
}

void Worm::Render()
{
	for (auto a : body)
		a->Render();
	Head->Render();
}

void Worm::Reflection(const D3DXVECTOR2 & n)
{
	velocity = velocity - 2 * D3DXVec2Dot(&velocity, &n) * n;
}

void Worm::VectorRotate(const float & angle)
{
	D3DXVECTOR2 prime;
	prime.x = velocity.x*cosf(angle) - velocity.y*sinf(angle);
	prime.y = velocity.x *sinf(angle) + velocity.y*cosf(angle);
	velocity = prime;
}

bool Worm::CollisionCheck(const D3DXVECTOR2 & pos, const float & colSize)
{
	D3DXVECTOR2 delta = position - pos; 
	if (D3DXVec2Dot(&delta, &delta) < colSize*colSize)
		return true;
	return false;
}

void Worm::Grow(int amount)
{
	length+=amount;

	for (int i = 0; i < amount; i++) {
		Sprite* cider = new Sprite(Textures + L"Bullets.png", Shaders + L"008_Sprite.fx", 252, 325, 270, 343);
		cider->Position(position);
		body.push_back(cider);
		velocity *= 1.04;
	}
}
