#pragma once
#include <raylib.h>
#include <animation.h>

class Attack
{
public:
	Attack(float xPos, float yPos);
	~Attack();
	bool isActive;
	void Draw();
	
private:
	Vector2 position;
	float width;
	float height;
};