#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile
{
private:
	float m_width; // square shape, same height and width
	int m_pathCost;
	bool m_marked{ false };

	sf::Vector2i m_rowCol{};
	sf::RectangleShape m_rect;
	sf::Text m_costText;
	sf::Vertex m_line[2];

	// colors
	sf::Color m_defaultColor = { 0, 87, 227, 255 };
	sf::Color m_pathColor = { 252, 186, 3, 255 };

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
	bool& marked() { return m_marked; }
	sf::Vector2i& rowCol() { return m_rowCol; }

	void setPosition(float x, float y);
	void setColor(sf::Color color) { m_rect.setFillColor(color); }

};

#endif // !TILE_H