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
	void setIsUsed(bool in_isUsed);
	Vec2 getPos() const;
private:
	const Color color = Colors::White;
	Vec2 pos;
	Vec2 vel;
	bool isUsed = false;
};