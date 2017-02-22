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
#include "Surface.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ship( Vec2( 200.0f, 300.0f), Vec2(0.0f,0.0f),Vec2(0.0f,0.0f)),
	laserSound( L"laser.wav"),
	explosionSound( L"explosion.wav"),
	collisionSound( L"collision.wav"),
	coinSound( L"coin.wav")
{
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
		
		if (wnd.kbd.KeyIsPressed(VK_UP)) 
		{
			ship.Accelerate();
			isShipAcc = true;
		}
		else
		{
			ship.SetAcc(Vec2(0.0f, 0.0f));
			isShipAcc = false;
			ship.Friction();
		}
		
		if (wnd.kbd.KeyIsPressed(VK_RIGHT)) 
		{
			ship.Rotate(-0.1f);
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT)) 
		{
			ship.Rotate(0.1f);
		}
		if (wnd.kbd.KeyIsPressed(VK_SPACE)) 
		{
			if (spaceBarCooldown.HasTimePassed(0.2f))
			{
				const float size = ship.GetSize();
				const float rotation = ship.GetRotation();
				spaceBarCooldown.Mark();
				bool recycledLaser = false;
				for (int i = 0; i < nLasers; i++)
				{
					if (!lasers[i].GetIsUsed())
					{

						lasers[i].Spawn(ship.GetPos() += Vec2(size*cosf(rotation), -size*sinf(rotation)),
							Vec2(300.0f * cosf(ship.GetRotation()), -300.0f * sinf(ship.GetRotation())));
						recycledLaser = true;
						break;
					}
				}

				if (nLasers < maxLaser - 1 && !recycledLaser) {

					lasers[nLasers].Spawn(ship.GetPos() += Vec2(size*cosf(rotation), -size*sinf(rotation)),
						Vec2(300.0f * cosf(ship.GetRotation()), -300.0f * sinf(ship.GetRotation())));
					nLasers++;
				}
				laserSound.Play();
			}
		}
		
		const float dt = ft.Mark();
		for (int i = 0; i < nAsteroids; i++) {
			asteroids[i].Update(dt, gfx);
			asteroids[i].Rotate();
			if (asteroids[i].CheckShipCollision(ship)) 
			{
				gameOver = true;
				collisionSound.Play();
				break;
			}
			for (int j = 0; j < nLasers; j++)
			{
				if (lasers[j].GetIsUsed() )
				{
					if (asteroids[i].CheckLaserCollision(lasers[j])) 
					{
						lasers[j].SetIsUsed(false);
						score++;
						asteroids[i].Spawn( rng, gfx, ship);
						explosionSound.Play();
					}
				}
			}
			
		}
		ship.Update( dt, gfx);
		for (int i = 0; i < nLasers; i++)
		{
			if (lasers[i].GetIsUsed() )
			{
				lasers[i].Update(dt, gfx);
			}
		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			gameOver = false;
			score = 0;
			ship.Reset(Vec2(200.0f, 300.0f), Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f));
			for (int i = 0; i < nAsteroids; i++)
			{
				asteroids[i].Spawn(rng, gfx, ship);
			}
			for (int i = 0; i < nLasers; i++)
			{
				lasers[i].Reset();
			}
			ft.Mark();
		}
	}
	
}

void Game::ComposeFrame()
{
	if (!gameOver)
	{
		for (int i = 0; i < nAsteroids; i++) 
		{
			asteroids[i].Draw(gfx);
		}
 		for (int j = 0; j < nLasers; j++)
		{
			if (lasers[j].GetIsUsed() ) 
			{
				lasers[j].Draw(gfx);
			}
		}
		if (isShipAcc)
		{
			ship.DrawPropulsion(gfx);
		}
		ship.Draw(gfx);
		int x = 250;
		int y = 250;

		x = 100;
		y = gfx.ScreenHeight - 100;
	}
	else
	{
		static const Surface infoImage = Surface::FromFile(L"info.png");
		gfx.DrawSpriteKey(100, gfx.ScreenHeight - 100, infoImage, infoImage.GetPixel(0, 0));

		static const Surface titleImage = Surface::FromFile(L"title.png");
		gfx.DrawSpriteKey(200, 200, titleImage, titleImage.GetPixel(0, 0));

	}

	const TextSurface::Font fontus(L"Hyperspace Negrita", 20.0f);
	std::wstring string = ("Score: ", std::to_wstring(score));
	gfx.DrawText(string, { 20.0f,20.0f }, fontus, Colors::White);
}
