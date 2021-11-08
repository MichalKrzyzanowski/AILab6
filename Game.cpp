#include "Game.h"

/// <summary>
/// default constructor
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 750, 750 }, "SFML Starter" }
{
	for (int i{}; i < 50; ++i)
	{
		for (int j{}; j < 50; ++j)
		{
			m_tiles[i][j].setPosition(m_tiles[i][j].width() * i, m_tiles[i][j].width() * j);
		}
	}

	// initial goal and start
	m_tiles[0][0].setColor(sf::Color::Green);
	m_start = &m_tiles[0][0];

	m_tiles[49][49].setColor(sf::Color::Red);
	m_goal = &m_tiles[49][49];
}

/// <summary>
/// game loop @ 60 fps
/// </summary>
void Game::run()
{
	sf::Clock clock{};
	sf::Time timeSinceLastUpdate{ sf::Time::Zero };
	sf::Time timePerFrame{ sf::seconds(1.0f / 60.f) }; // 60 fps

	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

/// <summary>
/// check for input
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		// quit when ESC is pressed or when the window is closed manually
		if ((sf::Keyboard::Escape == newEvent.key.code) ||
			sf::Event::Closed == newEvent.type)
		{
			m_window.close();
		}
		if (sf::Event::KeyReleased == newEvent.type && sf::Keyboard::E == newEvent.key.code)
		{
			m_placeWallMode = !m_placeWallMode;
		}
	}
}

/// <summary>
/// update the game world @ 60 fps
/// <param name="t_deltaTime">frame time</param>
void Game::update(sf::Time t_deltaTime)
{
	for (int i{}; i < 50; ++i)
	{
		for (int j{}; j < 50; ++j)
		{
			if (m_tiles[i][j].getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				if (m_placeWallMode)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						m_tiles[i][j].setColor(sf::Color::Black);
					}

					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						m_tiles[i][j].setColor(m_tiles[i][j].color());
					}
				}
				else
				{
					// set start tile
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						m_start->setColor(m_start->color());
						m_tiles[i][j].setColor(sf::Color::Green);
						m_start = &m_tiles[i][j];
					}

					// set goal tile
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						m_goal->setColor(m_start->color());
						m_tiles[i][j].setColor(sf::Color::Red);
						m_goal = &m_tiles[i][j];
					}
				}
			}
		}
	}
}

/// <summary>
/// draw the screen
/// </summary>
void Game::render()
{
	m_window.clear();

	for (int i{}; i < 50; ++i)
	{
		for (int j{}; j < 50; ++j)
		{
			m_tiles[i][j].render(&m_window);
		}
	}

	m_window.display();
}