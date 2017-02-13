#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include <random>

class Asteroid
{
public:
	Asteroid() = default;
	//Asteroid(std::mt19937& rng, const Graphics& gfx);
	void Spawn(std::mt19937& rng, const Graphics& gfx, const Vec2& inpos, const Vec2& invel);
	void Draw(Graphics& gfx) const;
	void Update(float dt, const Graphics& gfx);
	void Rotate();
private:
	static constexpr int nPoints = 6;
	int points[6];
	const Color color = Colors::White;
	float rotation = 0.0f;
	float rotationRate = 0.0f;
	Vec2 pos;
	Vec2 vel;
	float size = 20.0f;
	bool isDestroyed = false;
};
