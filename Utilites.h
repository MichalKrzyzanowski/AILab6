#ifndef UTILITIES_H
#define UTILITIES_H

#include <algorithm>

inline float manhattanDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	sf::Vector2i diff{};

	diff.x = b.x - a.x;
	diff.x = b.y - a.y;

	if (diff.x < 0) diff.x = -diff.x;
	if (diff.y < 0) diff.y = -diff.y;

	return diff.x + diff.y;
}

inline float chebyshevDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return std::max(abs(a.x - b.x), abs(a.y - b.y));
}

inline float euclideanDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sqrtf(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
}

inline sf::Vector2f normalize(const sf::Vector2f& v)
{
	float len = sqrtf(v.x * v.x + v.y * v.y);

	if (len != 0.0f) return sf::Vector2f{ v.x / len, v.y / len };

	return sf::Vector2f {};
}

#endif // !UTILITIES_H