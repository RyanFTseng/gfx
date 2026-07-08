#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"
#include "Drawable.h"


//transforms polylines to center origin by translating by 1/2 screenwidth and 1/2 screenheight
class CoordinateTransformer
{
public:
	CoordinateTransformer(Graphics& gfx)
		:
		gfx(gfx)
	{}
	void Draw(Drawable& drawable) const
	{
		Vec2 offset = { float(Graphics::ScreenWidth / 2), float(Graphics::ScreenHeight / 2) };
		drawable.ApplyTransformation(
			Mat3::Translation(offset.x, offset.y)*
			Mat3::ScaleIndependent(1.0f, -1.0f) 
			
		);
		drawable.Render(gfx);
	}

private:
	Graphics& gfx;
};