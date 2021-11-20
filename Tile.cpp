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
}

void Tile::setText(sf::Font& font)
{
	m_costText.setFont(font);
	m_costText.setCharacterSize(10u);
	m_costText.setFillColor(sf::Color(36u, 36u, 36u));
	m_costText.setString(std::to_string(m_pathCost));
}

void Tile::render(sf::RenderWindow* window, bool showNumbers)
{
	window->draw(m_rect);
	if(showNumbers) window->draw(m_costText);
}

void Tile::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);
	m_costText.setPosition(x, y);
}
