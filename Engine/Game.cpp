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
#include "ChiliMath.h"
#include "Mat3.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ct(gfx),
	cam(ct),
	plank({ 100.0f,200.0f }, -380.0f, -100.0f, 290.0f),
	spawn(balls, 15.0f, { 0.0f,-250.0f }, -100.0f, 25.0f, 150.0f, 2.0f)
{
	
	sf.generateField();
	
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



	const float dt = ft.Mark();

	t += dt;
	
	star = Star::Make(150.0f, 60.0f);
	const float theta = t * PI;

	for (auto& pt : star)
	{
		pt.Rotate(theta);
	}

	

	//for (auto& ball : balls)
	//{
	//	const auto plankPts = plank.GetPoints();
	//	
	//	const auto plankVector = plank.GetPlankSurfaceVector();
	//	const auto plankNormal = Vec2{ plankVector.y, -plankVector.x };
	//	const auto ballPos = ball.GetPos();

	//	if (plankNormal * ball.GetVel() < 0.0f)
	//	{
	//		if (DistancePointLine(plankPts.first, plankPts.second, ball.GetPos()) < ball.GetRadius())
	//		{

	//			const Vec2 w = plank.GetPlankSurfaceVector().GetNormalized();
	//			const Vec2 v = ball.GetVel();
	//			ball.SetVel((w * (v * w) * 2.0f - v));
	//			collideSound.Play();
	//		}
	//	}

	//	

	//	ball.Update(dt);
	//}
	//spawn.Update(dt);


	//const float speed = 3.0f;
	//if (wnd.kbd.KeyIsPressed(VK_DOWN))
	//{
	//	plank.MoveFreeY(-2.0f);
	//}
	//if (wnd.kbd.KeyIsPressed(VK_UP))
	//{
	//	plank.MoveFreeY(2.0f);
	//}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		cam.SetAngle(cam.GetAngle()- 0.1);
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		cam.SetAngle(cam.GetAngle() + 0.1);
	}

	//const auto new_end = std::remove_if(balls.begin(), balls.end(),
	//	[this](const Ball& b)
	//	{
	//		return b.GetPos().LenSq() > maxBallDistance * maxBallDistance;
	//	});
	//balls.erase(new_end, balls.end());
	//

	while (!wnd.mouse.IsEmpty())
	{
		

		const auto e = wnd.mouse.Read();
		//save mouse pos on click
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			prevMouseX = e.GetPosX();
			prevMouseY = e.GetPosY();
			
		}
		//check if mouse is moving and mouse is pressed down
		else if (e.GetType() == Mouse::Event::Type::Move && wnd.mouse.LeftIsPressed())
		{
			float xSpeed = prevMouseX - (float)e.GetPosX();
			float ySpeed = prevMouseY - (float)e.GetPosY();
			cam.MoveBy(Vec2{ xSpeed / cam.GetScale(), -ySpeed / cam.GetScale() }.Rotate(-cam.GetAngle()));
			prevMouseX = e.GetPosX();
			prevMouseY = e.GetPosY();
		}
		
		
		if (e.GetType() == Mouse::Event::Type::WheelUp)
		{
			cam.SetScale(cam.GetScale() * 1.05f);
		}
		else if (e.GetType() == Mouse::Event::Type::WheelDown)
		{
			cam.SetScale(cam.GetScale() * 0.95f);
		}
	}
	for (auto& entity : sf.getEntities())
	{
		entity.Update(dt);

	}
	
}

void Game::ComposeFrame()
{

	//render pipeline: 
	//Camera((Coordinate Transformer(Drawable(gfx draw polyline))))
	//camera transformations -> coordinate to center origin -> model -> line
	//model vertices stored in entity

	//cam.Draw(Drawable(star, Colors::Yellow));
	
	const auto vp = cam.getViewportRect();
	/*cam.Draw(plank.GetDrawable());
	for (const auto& ball : balls)
	{
		cam.Draw(ball.GetDrawable());
	}*/

	/*for (auto& entity : sf.getEntities())
	{
		if (entity.GetBoundingRectangle().IsOverlappingWith(vp))
		{

			cam.Draw(entity.GetDrawable());
		}
	}*/

	auto star = Star::Make(100.0f, 50.0f);
	const auto tform = Mat3::Rotation(0.3f);
	const auto tform2 = Mat3::Scale(2.0f);
	const auto tform3 = Mat3::FlipY();
	const auto tform4 = Mat3::Translation(200.0f, 100.0f);
	const auto tformcat = tform4 * tform3 * tform2 * tform;

	for (auto& v : star)
	{
		auto v3 = (Vec3)v;
		v = Vec2(tformcat * v3);
	}
	cam.Draw(Drawable{ star, Colors::Green });
	
}

