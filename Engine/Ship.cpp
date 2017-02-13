#include "Ship.h"
#include <math.h>

# define M_PI 3.14159f


Ship::Ship(const Vec2& in_pos, const Vec2& in_vel, const Vec2& in_acc)
	:
	pos(in_pos),
	vel(in_vel),
	acc(in_acc)

{
}

void Ship::Draw(Graphics& gfx) const
{
	gfx.DrawTriangle( pos.x + size*cosf(rotation), pos.y - size*sinf(rotation),
		pos.x + size * cosf(rotation + 0.75f*M_PI), pos.y - size * sinf(rotation + 0.75f*M_PI),
		pos.x + size * cosf(rotation + 1.25f*M_PI), pos.y - size * sinf(rotation + 1.25f*M_PI),
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

void Ship::Accelerate()
{
	acc += Vec2( 300.0f * cosf(rotation), -300.0f * sinf(rotation) );
}
void Ship::Friction()
{
	vel *= 0.99f;
}
void Ship::Update(float dt, const Graphics& gfx)
{
	vel += acc*dt;
	pos += vel*dt;
	int width = gfx.ScreenWidth;
	int height = gfx.ScreenHeight;
	/*if (pos.x < 0) {
		pos.x = width - pos.x;
	}
	else if (pos.x >= height) {
		pos.x -= height;
	}
	if (pos.y < 0) {
		pos.y = height - pos.y;
	}
	else if (pos.y >= height) {
		pos.y -= height;
	}*/
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

