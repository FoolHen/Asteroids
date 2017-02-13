#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include <random>

class Asteroid
{
public:
	Asteroid() = default;
	Asteroid(const Vec2& in_pos, const Vec2& in_vel);
	void Draw(Graphics& gfx) const;
	void Update(float dt, const Graphics& gfx);
	void Rotate();
private:
	const int nPoints = 6;
	int points[6];
	const Color color = Colors::White;
	float rotation = 0.0f;
	Vec2 pos;
	Vec2 vel;
	float size = 20.0f;
	std::mt19937 rng;
	bool isDestroyed = false;
};
