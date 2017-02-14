#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Laser
{
public:
	Laser() = default;
	void Spawn( const Vec2& in_pos, const Vec2& in_vel);
	void Draw( Graphics& gfx) const;
	void Update(float dt, const Graphics& gfx);
	void Reset();
	bool getIsUsed();
private:
	const Color color = Colors::Blue;
	Vec2 pos;
	Vec2 vel;
	bool isUsed = false;
};