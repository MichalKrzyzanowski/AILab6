#include "Tile.h"

Tile::Tile(float width) :
	m_width{ width }
{
	//m_font = nullptr;
	m_pathCost = 999;
	m_integration = 999;
	m_rect.setFillColor(m_defaultColor);
	m_rect.setSize(sf::Vector2f{ m_width, m_width });
	m_rect.setPosition(sf::Vector2f{});
	m_rect.setOutlineThickness(0.5f);
	m_rect.setOutlineColor(sf::Color::Black);

	m_line[0].color = m_vectorColor;
	m_line[1].color = m_vectorColor;
}

void Tile::setText(sf::Font& font)
{
	m_costText.setFont(font);
	m_costText.setCharacterSize(10u);
	m_costText.setFillColor(sf::Color::White);
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
}

void Tile::updateVector()
{
	m_vector = normalize(m_vector);

	m_vector.x *= m_width / 2.0f;
	m_vector.y *= m_width / 2.0f;

	m_line[1].position = m_line[0].position - m_vector;
}
