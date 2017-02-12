#include "Ship.h"
#include <math.h>

# define M_PI 3.14159


Ship::Ship(const Vec2& in_pos, const Vec2& in_vel, const Vec2& in_acc)
	:
	pos(in_pos),
	vel(in_vel),
	acc(in_acc)

{
}

void Ship::Draw(Graphics& gfx) const
{
	gfx.DrawTriangle( pos.x + 30.0f*cosf(rotation), pos.y - 30.0f*sinf(rotation),
		pos.x + 30.0f * cosf(rotation + 0.75f*M_PI), pos.y - 30.0f * sinf(rotation + 0.75f*M_PI),
		pos.x + 30.0f * cosf(rotation + 1.25f*M_PI), pos.y - 30.0f * sinf(rotation + 1.25f*M_PI),
		color);
}

void Ship::setAcc(Vec2 vec)
{
	acc.x = vec.x;
	acc.y = vec.y;
}

void Ship::setVel(Vec2 vec)
{
	vel.x = vec.x;
	vel.y = vec.y;
}

void Ship::setPos(Vec2 vec)
{
	pos.x = vec.x;
	pos.y = vec.y;
}

Vec2 Ship::getAcc() const
{
	return acc;
}

Vec2 Ship::getVel() const
{
	return vel;
}

Vec2 Ship::getPos() const
{
	return pos;
}

void Ship::Update(float dt)
{
	vel += acc*dt;
	pos += vel*dt;

}

void Ship::Rotate(const float & angle)
{
	rotation += angle;
	if (rotation < 0.0f) {
		rotation += 2 * M_PI;
	}
	else if (rotation >= 2 * M_PI) {
		rotation -= 2 * M_PI;
	}
}

