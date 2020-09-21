#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed)
{
	sprite = new Sprite(Textures + L"Bullets.png", shaderFile, 252, 325, 270, 343);

	position = start;
	sprite->Position(position);

	float radian = Math::ToRadian(angle);
	velocity.x = cosf(radian);
	velocity.y = sinf(radian);
	velocity *= speed;
}

Bullet::~Bullet()
{
	SAFE_DELETE(sprite);
}

void Bullet::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (position.x < 0)
		Reflection(D3DXVECTOR2(1, 0));
	if (position.x > Width)
		Reflection(D3DXVECTOR2(-1, 0));
	if (position.y < 0)
		Reflection(D3DXVECTOR2(0, 1));
	if (position.y > Height)
		Reflection(D3DXVECTOR2(0, -1));

	position += velocity;

	sprite->Position(position);
	sprite->Update(V, P);
}

void Bullet::Reflection(const D3DXVECTOR2 & n)
{
	velocity = velocity - 2 * D3DXVec2Dot(&velocity, &n) * n;
}

void Bullet::VectorRotate(const float & angle)
{
	D3DXVECTOR2 prime;
	prime.x = velocity.x*cosf(angle) - velocity.y*sinf(angle);
	prime.y = velocity.x *sinf(angle) + velocity.y*cosf(angle);
	velocity = prime;
}

void Bullet::Render()
{
	sprite->Render();
}

