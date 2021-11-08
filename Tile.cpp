#include "Tile.h"

Tile::Tile(float width) :
	m_width{ width }
{
	m_color.r = 0;
	m_color.g = 87;
	m_color.b = 227;
	m_color.a = 255;
	m_rect.setFillColor(m_color);
	m_rect.setSize(sf::Vector2f{ m_width, m_width });
	m_rect.setPosition(sf::Vector2f{});
	m_rect.setOutlineThickness(0.5f);
	m_rect.setOutlineColor(sf::Color::Black);
}

void Tile::render(sf::RenderWindow* window)
{
	window->draw(m_rect);
}
