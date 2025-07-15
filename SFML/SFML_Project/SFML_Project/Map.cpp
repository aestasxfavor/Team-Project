#include "Map.h"

void Map::Load(const std::string filename)
{
	texture.loadFromFile(GetrscPath(filename));
	spriteMap.setTexture(texture);
	//spriteMap.setTextureRect(sf::IntRect(10,400,2400,1800));
	//추가
	texture.setRepeated(true);
	spriteMap.setTextureRect(sf::IntRect(10, 323,1270, 1250));

}

void Map::Render(sf::RenderWindow& window)
{
	window.draw(spriteMap);
}

bool Map::IsWall(int x, int y) const
{
    return false;
}

//추가
void Map::Render(sf::RenderWindow& window, const sf::Vector2f& playerPosition)
{
    const int tileW = 1270;
    const int tileH = 1250;

    int baseX = static_cast<int>(playerPosition.x) - 400;
    int baseY = static_cast<int>(playerPosition.y) - 300;

    baseX = (baseX / tileW) * tileW;
    baseY = (baseY / tileH) * tileH;

    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            spriteMap.setPosition(float(baseX + i * tileW), float(baseY + j * tileH));
            window.draw(spriteMap);
        }
    }
}
