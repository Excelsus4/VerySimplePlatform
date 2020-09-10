#pragma once
#include "Draws/Rect.h"

class Player :
	public Rect
{
public:
	Player(wstring shaderFile);
	Player(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color = D3DXCOLOR(1, 1, 1, 1));
	virtual ~Player();

	virtual void Update() override;

	void MoveLeft();
	void MoveRight();

	void Speed(float val) { speed = val; }
	float Speed() { return speed; }
	void Strength(float val) { jumpStrength = val; }
	float Strength() { return jumpStrength; }

	void StartJump();
	void EndJump();

	void AutoMove();

private:
	float speed;
	float gravity;
	float jumpStrength;

	float velocity;
	bool bOnGround;

	bool bHeadingLeft;
};

