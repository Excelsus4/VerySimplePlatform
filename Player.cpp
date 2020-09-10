#include "stdafx.h"
#include "Player.h"

Player::Player(wstring shaderFile):
	Rect(shaderFile),speed(250.0f),velocity(0.0f),gravity(-1.5f),bOnGround(true), bHeadingLeft(true), jumpStrength(0.6f)
{
}

Player::Player(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color):
	Rect(shaderFile),speed(250.0f), velocity(0.0f),gravity(-1.5f),bOnGround(true), bHeadingLeft(true), jumpStrength(0.6f)
{
}

Player::~Player()
{
}

void Player::Update()
{
	__super::Update();
	D3DXVECTOR2 position = Position();
	velocity += gravity * Time::Delta();

	if (bOnGround == false) {
		position.y += velocity;
		Position(position);
	}
	if (position.y < Scale().y*0.5f) {
		position.y = Scale().y*0.5f;
		velocity = 0.0f;
		
		bOnGround = true;

		Position(position);
	}
}

void Player::MoveLeft()
{
	D3DXVECTOR2 position = Position();
	position.x -= speed * Time::Delta();

	Position(position);
}

void Player::MoveRight()
{
	D3DXVECTOR2 position = Position();
	position.x += speed * Time::Delta();

	Position(position);
}

void Player::StartJump()
{
	if (bOnGround == true) {
		velocity = jumpStrength;
		bOnGround = false;
	}
}

void Player::EndJump()
{
	if (velocity > jumpStrength / 3)
		velocity = jumpStrength / 3;
}

void Player::AutoMove()
{
	D3DXVECTOR2 position = Position();
	if (bHeadingLeft) {
		MoveLeft();
		if (position.x < Scale().x*0.5f) {
			position.x = Scale().x*0.5f;
			bHeadingLeft = false;
		}
	}
	else {
		MoveRight();
		if (position.x > Width - Scale().x*0.5f) {
			position.x = Width - Scale().x*0.5f;
			bHeadingLeft = true;
		}
	}
}
