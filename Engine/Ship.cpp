#include "Ship.h"


Ship::Ship(Vec2 in_pos)
{
	pos = in_pos;
}

void Ship::Draw(Graphics& gfx) const
{
	gfx.DrawTriangle( int(pos.x), int(pos.y - 10), int(pos.x + 10), int(pos.y + 10), int(pos.x -10), int(pos.y + 10), color);
}
