#pragma once
#include "Star.h"
#include "Starbro.h"
#include <random>
#include <algorithm>

class Starfield
{
public:
	Starfield(float width, float height)
		:
		width(width),
		height(height)
		

	{}

	std::vector<Starbro> getEntities()
	{
		return stars;
	}

	void generateField()
	{
		std::random_device dev;
		//generate random num
		std::mt19937 rng(dev());
		std::uniform_real_distribution<float> xDist(-width / 2.0f, width / 2.0f);
		std::uniform_real_distribution<float> yDist(-height / 2.0f, height / 2.0f);
		std::normal_distribution<float> radDist(meanStarRadius, devStarRadius);
		std::normal_distribution<float> ratDist(meanInnerRatio, devInnerRatio);
		std::normal_distribution<float> flareDist(meanFlares, devFlares);
		const Color colors[] = { Colors::Red, Colors::White, Colors::Yellow, Colors::Magenta, Colors::Blue, Colors::Cyan, Colors::Green };
		std::uniform_int_distribution<size_t> colorSampler(0, std::end(colors) - std::begin(colors));

		while (stars.size() < nStars)
		{
			//generate radius and position
			const auto rad = std::clamp(radDist(rng), minStarRadius, maxStarRadius);
			const Vec2 pos = { xDist(rng), yDist(rng) };
			//check for overlaps with star
			if (std::any_of(stars.begin(), stars.end(), [&](const Starbro& sb)
			{
				//check new star against each existing star(sb)
				//check if distance between the star postitions is less than the sum of the distance between their radii
				//overlap detected if true
				return (sb.GetPos() -pos).Len() < rad + sb.GetRadius(); }))
			{
				//retry if overlap detected
				continue;
			}

			//generate star parameters
			const auto rat = std::clamp(ratDist(rng), minInnerRatio, maxInnerRatio);
			const Color c = colors[colorSampler(rng)];
			const int nFlares = std::clamp((int)flareDist(rng), minFlares, maxFlares);
			//place star in container
			stars.emplace_back(pos, rad, rat, nFlares, c);
		}

		
	}

private:
	static constexpr int nStars = 500;
	static constexpr float meanStarRadius = 160.0f;
	static constexpr float devStarRadius = 90.f;
	static constexpr float minStarRadius = 40.f;
	static constexpr float maxStarRadius = 300.f;
	static constexpr float meanInnerRatio = 0.4f;
	static constexpr float devInnerRatio = 0.25;
	static constexpr float minInnerRatio = 0.15;
	static constexpr float maxInnerRatio = 0.8;
	static constexpr float meanFlares = 6.5f;
	static constexpr float devFlares = 2.0f;
	static constexpr int minFlares = 3;
	static constexpr int maxFlares = 10;



	float height;
	float width;
	std::vector<Starbro> stars;
};