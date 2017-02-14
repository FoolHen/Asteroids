#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include <random>

class Asteroid
{
public:
	Asteroid() = default;
	void Spawn(std::mt19937& rng, const Graphics& gfx, const Vec2& inpos, const Vec2& invel);
	void Draw(Graphics& gfx) const;
	void Update(float dt, const Graphics& gfx);
	void Rotate();
	bool GetDestroyed() const;
private:
	static constexpr int maxVertex = 12;
	const Color color = Colors::White;

	int nVertex = 6;
	int distances[maxVertex];
	
	float rotation = 0.0f;
	float rotationRate = 0.0f;
	Vec2 pos;
	Vec2 vel;
	bool isDestroyed = false;
};
