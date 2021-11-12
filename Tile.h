#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
private:
	float m_width; // square shape, same height and width
	int m_pathCost;
	sf::RectangleShape m_rect;
	sf::Color m_color;

public:
	Tile(float width = 15.0f);
	
	void render(sf::RenderWindow* window);
	
	sf::Vector2f position() { return m_rect.getPosition(); }
	float width() { return m_width; }
	sf::FloatRect getGlobalBounds() { return m_rect.getGlobalBounds(); }
	sf::Color color() { return m_color; }

	int& pathCost() { return m_pathCost; }

	void setPosition(float x, float y) { m_rect.setPosition(x, y); }
	void setColor(sf::Color color) { m_rect.setFillColor(color); }

};

#endif // !TILE_H