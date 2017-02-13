#include "Asteroid.h"
#include <math.h>

# define M_PI 3.14159f

Asteroid::Asteroid(const Vec2 & in_pos, const Vec2 & in_vel)
	:
	pos(in_pos),
	vel(in_vel)
{
	std::uniform_int_distribution<int> rDist(10, 25);
	for (int i = 0; i < nPoints; i++) {
		points[i] = rDist(rng);
	}
}

void Asteroid::Draw(Graphics & gfx) const
{
	for (int i = 0; i < nPoints-1; i++)
	{
		gfx.DrawLine(pos.x + points[i] * cosf(float(i) * M_PI / 3.0f + rotation), pos.y - points[i] * sinf(float(i) * M_PI / 3.0f + rotation),
			pos.x + points[i + 1] * cosf(float(i + 1) * M_PI / 3.0f + rotation), pos.y - points[i + 1] * sinf(float(i + 1) * M_PI / 3.0f + rotation),
			color);
	}
	gfx.DrawLine(pos.x + points[5] * cosf(float(5) * M_PI / 3.0f + rotation), pos.y - points[5] * sinf(float(5) * M_PI / 3.0f + rotation),
		pos.x + points[0] * cosf(float(0) * M_PI / 3.0f + rotation), pos.y - points[0] * sinf(float(0) * M_PI / 3.0f + rotation),
		color);
}

void Asteroid::Update(float dt, const Graphics & gfx)
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
}

void Asteroid::Rotate()
{
	rotation += 0.05f;
	if (rotation < 0.0f) {
		rotation += 2 * M_PI;
	}
	else if (rotation >= 2 * M_PI) {
		rotation -= 2 * M_PI;
	}
}
