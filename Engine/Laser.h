#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "FrameTimer.h"

class Laser
{
public:
	Laser() = default;
	void Spawn( const Vec2& in_pos, const Vec2& in_vel);
	void Draw( Graphics& gfx) const;
	void Update(float dt, const Graphics& gfx);
	void Reset();
	bool GetIsUsed();
	void SetIsUsed(bool in_isUsed);
	
	Vec2 GetPos() const;
private:
	const Color color = Colors::White;
	Vec2 pos;
	Vec2 vel;
	FrameTimer ft;
	bool isUsed = false;
};