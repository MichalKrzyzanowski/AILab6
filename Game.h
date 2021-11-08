#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	sf::RenderWindow m_window;

	bool m_placeWallMode{ false };

	Tile m_tiles[50][50]{};
	
	Tile* m_start{ nullptr };
	Tile* m_goal{ nullptr };
};

#endif // !GAME_H
