#pragma once

#include "Vec2.h"
#include "Graphics.h"


class Ship
{
public:
	Ship() = default;
	Ship(const Vec2& in_pos, const Vec2& in_vel, const Vec2& in_acc);
	void Draw( Graphics& gfx) const;
	void setAcc(Vec2 vec);
	void setVel(Vec2 vec);
	void setPos(Vec2 vec);
	Vec2 getAcc() const;
	Vec2 getVel() const;
	Vec2 getPos() const;
	void Update(float dt);
	void Rotate(const float& angle);
private:
	const Color color = Colors::White;
	float rotation = 0.0f;
	Vec2 pos;
	Vec2 vel;
	Vec2 acc;
};

