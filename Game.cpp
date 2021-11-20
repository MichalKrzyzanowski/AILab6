#include "Game.h"

/// <summary>
/// default constructor
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 750, 750 }, "SFML Starter" }
{
	m_font.loadFromFile("Assets/CaviarDreams.ttf");

	for (int i{}; i < 50; ++i)
	{
		for (int j{}; j < 50; ++j)
		{
			m_tiles.at(i).at(j) = new Tile();
			m_tiles.at(i).at(j)->setText(m_font);
			m_tiles.at(i).at(j)->rowCol() = sf::Vector2i{ i, j };
			m_tiles.at(i).at(j)->setPosition(m_tiles.at(i).at(j)->width() * i, m_tiles.at(i).at(j)->width() * j);
		}
	}

	// initial goal and start
	m_tiles.at(0).at(0)->setColor(sf::Color::Green);
	m_start = m_tiles.at(0).at(0);

	m_tiles.at(49).at(49)->setColor(sf::Color::Red);
	m_goal = m_tiles.at(49).at(49);

	generateFlowField(m_start, m_goal);
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

		// edit mode
		if (sf::Event::KeyReleased == newEvent.type && sf::Keyboard::E == newEvent.key.code)
		{
			m_placeWallMode = !m_placeWallMode;
		}

		// show costs
		if (sf::Event::KeyReleased == newEvent.type && sf::Keyboard::Num1 == newEvent.key.code)
		{
			m_showCosts = !m_showCosts;
		}

		// show vectors
		if (sf::Event::KeyReleased == newEvent.type && sf::Keyboard::Num2 == newEvent.key.code)
		{
			m_showVectors = !m_showVectors;
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
			if (m_tiles.at(i).at(j)->getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				if (m_placeWallMode)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						if (m_tiles.at(i).at(j)->position() != m_start->position() ||
							m_tiles.at(i).at(j)->position() != m_goal->position())
						{
							m_tiles.at(i).at(j)->setColor(sf::Color::Black);
							generateFlowField(m_start, m_goal);
						}
					}

					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						m_tiles.at(i).at(j)->setColor(m_tiles.at(i).at(j)->defaultColor());
						generateFlowField(m_start, m_goal);
					}
				}
				else
				{
					// set start tile
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						if (m_tiles.at(i).at(j)->position() != m_goal->position())
						{
							m_start->setColor(m_start->defaultColor());
							m_start->updateColor();
							m_tiles.at(i).at(j)->setColor(sf::Color::Green);
							m_start = m_tiles.at(i).at(j);
						}
					}

					// set goal tile
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						if (m_tiles.at(i).at(j)->position() != m_start->position())
						{
							m_goal->setColor(m_start->defaultColor());
							m_tiles.at(i).at(j)->setColor(sf::Color::Red);
							m_goal = m_tiles.at(i).at(j);
							generateFlowField(m_start, m_goal);
						}
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
			m_tiles.at(i).at(j)->render(&m_window, m_showCosts, m_showVectors);
		}
	}

	m_window.display();
}

void Game::generateFlowField(Tile* start, Tile* goal)
{
	// reset
	for (int i{}; i < 50; ++i)
	{
		for (int j{}; j < 50; ++j)
		{
			m_tiles.at(i).at(j)->pathCost() = 999;
			m_tiles.at(i).at(j)->marked() = false;

			// reset color if not black
			if (m_tiles.at(i).at(j)->color() != sf::Color::Black)
			{
				m_tiles.at(i).at(j)->setColor(m_tiles.at(i).at(j)->defaultColor());
			}
		}
	}
	m_openList.empty();

	goal->pathCost() = 0;
	goal->updateText();
	goal->marked() = true;

	m_openList.push(goal);

	while (!m_openList.empty())
	{
		generateCostField(m_openList.front()->rowCol().x, m_openList.front()->rowCol().y);
		m_openList.pop();
	}

	goal->setColor(sf::Color::Red);
	start->setColor(sf::Color::Green);
}

void Game::generateCostField(int row, int col)
{
	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4) continue;
		int currentRow = row + ((direction % 3) - 1);
		int currentCol = col + ((direction / 3) - 1);

		if (currentRow >= 0 && currentRow < 50 && currentCol >= 0 && currentCol < 50)
		{
			// not a wall?
			if (m_tiles.at(currentRow).at(currentCol)->color() != sf::Color::Black)
			{
				// not marked?
				if (!m_tiles.at(currentRow).at(currentCol)->marked())
				{
					m_tiles.at(currentRow).at(currentCol)->pathCost() = m_tiles.at(row).at(col)->pathCost() + 1;
					m_tiles.at(currentRow).at(currentCol)->updateText();
					m_tiles.at(currentRow).at(currentCol)->updateColor();
					m_tiles.at(currentRow).at(currentCol)->marked() = true;
					m_openList.push(m_tiles.at(currentRow).at(currentCol));
				}
			}
		}
	}
}
