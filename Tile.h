#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include "Utilites.h"

class Tile
{
private:
	float m_width; // square shape, same height and width
	int m_pathCost;
	int m_integration;
	sf::Vector2f m_vector{};
	bool m_marked{ false };

	sf::Vector2i m_rowCol{};
	sf::Vector2i m_pathTile{};
	sf::RectangleShape m_rect;
	sf::Text m_costText;
	sf::Vertex m_line[2];

	// colors
	sf::Color m_defaultColor = { 0u, 87u, 227u, 255u };
	sf::Color m_pathColor = { 252u, 186u, 3u, 255u };
	sf::Color m_vectorColor = { 200u, 200u, 200u, 150u };

public:
	Tile(float width = 15.0f);
	
	void setText(sf::Font& font);
	void render(sf::RenderWindow* window, bool showNumbers, bool showVectors);
	
	sf::Vector2f position() { return m_rect.getPosition(); }
	float width() { return m_width; }
	sf::FloatRect getGlobalBounds() { return m_rect.getGlobalBounds(); }
	sf::Color color() { return m_rect.getFillColor(); }

	sf::Color defaultColor() { return m_defaultColor; }
	sf::Color pathColor() { return m_pathColor; }

	void updateText() { m_costText.setString(std::to_string(m_pathCost)); }
	void updateColor();

	int& pathCost() { return m_pathCost; }
	int& integration() { return m_integration; }
	bool& marked() { return m_marked; }

	sf::Vector2i& rowCol() { return m_rowCol; }
	sf::Vector2i& pathTile() { return m_pathTile; }
	sf::Vector2f& vector() { return m_vector; }

	void setPosition(float x, float y);
	void updateVector();
	void setColor(sf::Color color) { m_rect.setFillColor(color); }

};

#endif // !TILE_H