#ifndef UTILITIES_H
#define UTILITIES_H

inline float manhattanDistance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	sf::Vector2i diff{};

	diff.x = b.x - a.x;
	diff.x = b.y - a.y;

	if (diff.x < 0) diff.x = -diff.x;
	if (diff.y < 0) diff.y = -diff.y;

	return diff.x + diff.y;
}

inline sf::Vector2f normalize(const sf::Vector2f& v)
{
	float len = sqrtf(v.x * v.x + v.y * v.y);

	if (len != 0.0f) return sf::Vector2f{ v.x / len, v.y / len };

	return sf::Vector2f {};
}

#endif // !UTILITIES_H