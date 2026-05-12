#pragma once
#include "Entity.h"
#include "Star.h"

class Starbro : public Entity
{
public:
	Starbro(Vec2 pos, float radius, float innerRatio, int nFlares, Color c)
		:
		Entity(Star::Make(radius, radius * innerRatio, nFlares), pos, c),
		radius(radius)
	{}

	float GetRadius() const
	{
		return radius;
	}
private:
	float radius;
};