#include "Asteroid.h"
#include <math.h>

# define M_PI 3.14159f



void Asteroid::Spawn(std::mt19937 & rng, const Graphics & gfx, const Ship& ship)
	
{
	pos = Vec2(0.0f, 0.0f);
	vel = Vec2(0.0f,0.0f);

	std::uniform_int_distribution<int> nVertexDist(3, 12);
	nVertex = nVertexDist(rng);

	std::uniform_int_distribution<int> distanceDist(10, 40);
	for (int i = 0; i < nVertex; i++) {
		distances[i] = distanceDist(rng);
		averageDistance += distances[i];
	}
	averageDistance = averageDistance / float(nVertex);

	std::uniform_real_distribution<float> rotationDist(-0.05f, 0.05f);
	rotationRate = rotationDist(rng);

	
	std::uniform_int_distribution<int> xDist(100, gfx.ScreenWidth - 100);
	std::uniform_int_distribution<int> yDist(100, gfx.ScreenHeight - 100);
	std::uniform_real_distribution<float> vxDist(-120.0f, 120.0f);
	std::uniform_real_distribution<float> vyDist(-120.0f, 100.0f);
	
	do {
		pos.x = float(xDist(rng));
		pos.y = float(yDist(rng));
	} while (CheckSpawnCollision(ship, 60.0f));

	vel.x = vxDist(rng);
	vel.y = vyDist(rng);
}

void Asteroid::Draw(Graphics & gfx) const
{
	const float c = 2 * M_PI / float(nVertex);
	int i;
	for (i = 1; i < nVertex; ++i)
	{
		gfx.DrawLine(pos.x + distances[i-1] * cosf(float(i-1) * c + rotation), pos.y + distances[i-1] * sinf(float(i-1) * c + rotation),
			pos.x + distances[i] * cosf(float(i) * c + rotation), pos.y + distances[i] * sinf(float(i) * c + rotation),
			color);
	}
	gfx.DrawLine(pos.x + distances[i-1] * cosf(float(i-1) * c + rotation), pos.y + distances[i-1] * sinf(float(i-1) * c + rotation),
		pos.x + distances[0] * cosf(float(0) * c + rotation), pos.y + distances[0] * sinf(float(0) * c + rotation),
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

bool Asteroid::CheckSpawnCollision(const Ship & ship, float margin)
{
	bool collision = false;
	const Vec2 ship_pos = ship.GetPos();
	const float size = 0.5f * ship.GetSize();
	const float dist_sqr_x = abs((pos.x - ship_pos.x) * (pos.x - ship_pos.x));
	const float dist_sqr_y = abs((pos.y - ship_pos.y) * (pos.y - ship_pos.y));
	if (dist_sqr_x + dist_sqr_y < (size + averageDistance + margin) * (size + averageDistance + margin))
	{
		collision = true;
	}
	return collision;
}

bool Asteroid::CheckShipCollision(const Ship& ship)
{

	return CheckSpawnCollision(ship, 0.0f);
}

bool Asteroid::CheckLaserCollision(const Laser & laser)
{
	bool collision = false;
	const Vec2 laser_pos = laser.GetPos();
	const float dist_sqr_x = abs((pos.x - laser_pos.x) * (pos.x - laser_pos.x));
	const float dist_sqr_y = abs((pos.y - laser_pos.y) * (pos.y - laser_pos.y));
	if (dist_sqr_x + dist_sqr_y < (averageDistance) * (averageDistance))
	{
		collision = true;
	}
	return collision;
}

