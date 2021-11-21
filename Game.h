#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <queue>
#include "Tile.h"
#include "Utilites.h"

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	void generateFlowField();

	void generateCostField(int row, int col);
	void generateVectorField(int row, int col);
	void generatePath();

	sf::RenderWindow m_window;

	bool m_placeWallMode{ false };
	bool m_showCosts{ false };
	bool m_showVectors{ false };

	std::array<std::array<Tile*, 50>, 50> m_tiles{ nullptr };
	std::queue<Tile*> m_openList{};

	sf::Font m_font;
	
	Tile* m_start{ nullptr };
	Tile* m_goal{ nullptr };
};

#endif // !GAME_H
