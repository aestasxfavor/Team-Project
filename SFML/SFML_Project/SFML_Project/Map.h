#pragma once
#include "Util.h"

class Map
{
public:
	sf::Texture texture;
	sf::Sprite spriteMap;


	void Load(const string filename);
	void Render(sf::RenderWindow& window);
	bool IsWall(int x, int y)const;
	//Ãß°¡
	void Render(sf::RenderWindow& window, const sf::Vector2f& playerPosition);
};

