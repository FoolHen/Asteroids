#include "Asteroid.h"
#include <math.h>

# define M_PI 3.14159f

Asteroid::Asteroid( std::mt19937& rng, const Graphics& gfx)
{
	std::uniform_int_distribution<int> rDist(10, 25);
	std::uniform_int_distribution<int> xDist(0, gfx.ScreenWidth-1);
	std::uniform_int_distribution<int> yDist(0, gfx.ScreenHeight - 1);
	std::uniform_int_distribution<int> vxDist(0, 50);
	std::uniform_int_distribution<int> vyDist(0, 50);
	std::uniform_real_distribution<float> rotationDist(-0.05f, 0.00f);
	do {
		pos.x = float(xDist(rng));
		pos.y = float(yDist(rng));
	} while (true);//TODO COLLISION
	
	vel.x = float(vxDist(rng));
	vel.x = float(vxDist(rng));
	rotationRate = rotationDist(rng);
	for (int i = 0; i < nPoints; i++) {
		points[i] = rDist(rng);
	}

}

void Asteroid::Spawn(std::mt19937 & rng, const Graphics & gfx)
{
	std::uniform_int_distribution<int> rDist(10, 25);
	std::uniform_int_distribution<int> xDist(0, gfx.ScreenWidth - 1);
	std::uniform_int_distribution<int> yDist(0, gfx.ScreenHeight - 1);
	std::uniform_int_distribution<int> vxDist(0, 50);
	std::uniform_int_distribution<int> vyDist(0, 50);
	std::uniform_real_distribution<float> rotationDist(-0.05f, 0.00f);
	do {
		pos.x = float(xDist(rng));
		pos.y = float(yDist(rng));
	} while (true);//TODO COLLISION

	vel.x = float(vxDist(rng));
	vel.x = float(vxDist(rng));
	rotationRate = rotationDist(rng);
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
	rotation += rotationRate;
	if (rotation < 0.0f) {
		rotation += 2 * M_PI;
	}
	else if (rotation >= 2 * M_PI) {
		rotation -= 2 * M_PI;
	}
}
