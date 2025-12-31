#include <attack.h>

Attack::Attack(float xPos, float yPos)
{
	isActive = false;
	position.x = xPos;
	position.y = yPos;
}

void Attack::Draw()
{
	DrawRectangle(position.x, position.y, width, height, RED);
}
