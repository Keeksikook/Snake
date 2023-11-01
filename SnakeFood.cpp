#include "Snake.h"


unsigned long SnakeFood::nCreated = 0, SnakeFood::nAlive = 0;
SnakeFood::SnakeFood(sf::Vector2<float> pos, float radius)
	:
	Entity(pos)
{
	shape.setRadius(radius - 1);
	shape.setFillColor(sf::Color(50, 205, 50, 255));
	shape.setOrigin(radius / 2, radius / 2);
	shape.setPosition(pos);
	shape.setOutlineThickness(1);
	nCreated++;
	nAlive++;
}


SnakeFood::~SnakeFood()
{
	nAlive--;
}
