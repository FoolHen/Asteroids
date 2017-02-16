#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Ship.h"
#include "Laser.h"
#include <random>

class Asteroid
{
public:
	Asteroid() = default;
	void Spawn(std::mt19937& rng, const Graphics& gfx, const Ship& ship);
	void Draw(Graphics& gfx) const;
	void Update(float dt, const Graphics& gfx);
	void Rotate();
	bool CheckSpawnCollision(const Ship& ship, float margin);
	bool CheckShipCollision(const Ship& ship);
	bool CheckLaserCollision(const Laser& laser);
private:
	static constexpr int maxVertex = 12;
	const Color color = Colors::White;

	int nVertex = 6;
	int distances[maxVertex];
	float averageDistance = 0.0f;
	
	float rotation = 0.0f;
	float rotationRate = 0.0f;
	Vec2 pos;
	Vec2 vel;
};
