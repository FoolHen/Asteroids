#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Ship
{
public:
	Ship() = default;
	Ship(Vec2 in_pos);
	void Draw( Graphics& gfx) const;


private:
	const Color color = Colors::White;
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
};

