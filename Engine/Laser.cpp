#include "Laser.h"

void Laser::Spawn(const Vec2& in_pos, const Vec2& in_vel)
{
 	isUsed = true;
	pos.x = in_pos.x;
	pos.y = in_pos.y;
	vel.x = in_vel.x;
	vel.y = in_vel.y;
	ft.Mark();
}

void Laser::Draw( Graphics & gfx) const
{
	gfx.DrawCircle(int(pos.x), int(pos.y), 2, color);
}

void Laser::Update(float dt, const Graphics & gfx)
{
	pos += vel*dt;
	float width = gfx.ScreenWidth;
	float height = gfx.ScreenHeight;
	if (pos.x < 0.0f) {
		pos.x = width - 1.0f + pos.x;
	}
	else if (pos.x >= width) {
		pos.x -= width;
	}
	if (pos.y < 0.0f) {
		pos.y = height - 1.0f + pos.y;
	}
	else if (pos.y >= height) {
		pos.y -= height;
	}
	if (ft.HasTimePassed(1.2f))
	{
		isUsed = false;
	}
}

void Laser::Reset()
{
	isUsed = false;
}

bool Laser::GetIsUsed()
{
	return isUsed;
}

void Laser::SetIsUsed(bool in_isUsed)
{
	isUsed = in_isUsed;
}

Vec2 Laser::GetPos() const
{
	return pos;
}
