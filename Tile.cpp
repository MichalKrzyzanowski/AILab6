#include "Tile.h"

Tile::Tile(float width) :
	m_width{ width }
{
	//m_font = nullptr;
	m_pathCost = 999;
	m_rect.setFillColor(m_defaultColor);
	m_rect.setSize(sf::Vector2f{ m_width, m_width });
	m_rect.setPosition(sf::Vector2f{});
	m_rect.setOutlineThickness(0.5f);
	m_rect.setOutlineColor(sf::Color::Black);

	m_line[0].color = sf::Color(36u, 36u, 36u);
	m_line[1].color = sf::Color(36u, 36u, 36u);
}

void Tile::setText(sf::Font& font)
{
	m_costText.setFont(font);
	m_costText.setCharacterSize(10u);
	m_costText.setFillColor(sf::Color(36u, 36u, 36u));
	m_costText.setString(std::to_string(m_pathCost));
}

void Tile::render(sf::RenderWindow* window, bool showNumbers, bool showVectors)
{
	window->draw(m_rect);
	if(showNumbers) window->draw(m_costText);
	if (showVectors) window->draw(m_line, 2, sf::Lines);
}

void Tile::updateColor()
{
	int a = 255 - m_pathCost * 4;
	if (a < 0) a = 0;

	m_rect.setFillColor(sf::Color(m_defaultColor.r, m_defaultColor.g, m_defaultColor.b, a));
}

void Tile::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);
	m_costText.setPosition(x, y);
	m_line[0].position = sf::Vector2f{ x + m_width / 2.0f, y + m_width / 2.0f };
	m_line[1].position = sf::Vector2f{ x, y + m_width / 2.0f };
}
