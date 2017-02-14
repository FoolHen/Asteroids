/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ship( Vec2( 200.0f, 300.0f), Vec2(0.0f,0.0f),Vec2(0.0f,0.0f))
{
	/*for (int i = 0; i < nAsteroids ; i++)
	{
		asteroids[i].Spawn( rng,gfx,ship);
	}*/
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP)) {
			ship.Accelerate();
			isShipAcc = true;
		}
		else {
			ship.setAcc(Vec2(0.0f, 0.0f));
			isShipAcc = false;
			ship.Friction();
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
			ship.Rotate(-0.1f);
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
			ship.Rotate(0.1f);
		}

		const float dt = ft.Mark();
		for (int i = 0; i < nAsteroids; i++) {
			if (asteroids[i].GetDestroyed() == false) {
				asteroids[i].Update(dt, gfx);
				asteroids[i].Rotate();
				if (asteroids[i].checkShipCollision(ship)) {
					gameOver = true;
					break;
				}
				
			}

		}
		ship.Update(dt, gfx);
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			gameOver = false;
			ship.Reset(Vec2(200.0f, 300.0f), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
			for (int i = 0; i < nAsteroids; i++)
			{
				asteroids[i].Spawn(rng, gfx, ship);
			}
		}
	}
	
}

void Game::ComposeFrame()
{
	if (!gameOver)
	{
		for (int i = 0; i < nAsteroids; i++) {

			if (asteroids[i].GetDestroyed() == false) {
				asteroids[i].Draw(gfx);
				if (isShipAcc)
				{
					ship.DrawPropulsion(gfx);
				}
			}
		}
		ship.Draw(gfx);
	}
	else
	{

	}
}
