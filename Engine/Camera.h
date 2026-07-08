#pragma once

#include "CoordinateTransformer.h"
#include "RectF.h"
#include "Graphics.h"
#include "ChiliMath.h"

class Camera
{
public:
	Camera(CoordinateTransformer& ct)
		:
		ct(ct)
	{}
	Vec2 GetPos() const
	{
		return pos;
	}
	void MoveBy(const Vec2& offset)
	{

		pos += offset;
	
		
	}
	void MoveTo(const Vec2& pos_in)
	{
		
		pos = pos_in;
		
	}
	void Draw(Drawable& drawable) const
	{
		drawable.ApplyTransformation(
			Mat3::Translation(-pos.x, -pos.y)*
			Mat3::Rotation(angle) *
			Mat3::Scale(scale)
			
		);
		ct.Draw(drawable);
	}
	void SetScale(float s)
	{
		scale = s;
	}
	float GetScale() const
	{
		return scale;
	}
	void SetAngle(float a)
	{
		angle = a;
	}
	float GetAngle() const
	{
		return angle;
	}
	RectF getViewportRect() const
	{
		
		const float zoom = 1.0f / scale ;
		const float diagonal = sqrt(
			sq(float(Graphics::ScreenWidth / 2) * zoom) +
			sq(float(Graphics::ScreenHeight / 2) * zoom)
		);
		return RectF::FromCenter(
			pos, diagonal, diagonal);
	}

private:
	float angle = 0.0f;
	Vec2 pos = { 0.0f,0.0f };
	float scale = 1.0f;
	CoordinateTransformer& ct;
};