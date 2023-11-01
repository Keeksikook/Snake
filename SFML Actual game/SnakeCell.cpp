#include "Snake.h"



void SnakeCell::follow()
{
	const static constexpr float radius = 6;
	sf::Vector2<float> targetPos = followTarget->getPos();
	sf::Vector2<float> movePos = {targetPos.x - pos.x, targetPos.y - pos.y};
	vec::operator-=(movePos, 2*radius);
	pos += movePos;
	shape.setPosition(pos);
}

SnakeCell::SnakeCell(Entity* followTarget) :
	Entity(followTarget->getPos() - sf::Vector2<float>{12, 0}, {0, 0}),
	followTarget(followTarget)
{
	shape.setRadius(5);
	shape.setFillColor(sf::Color(180, 180, 180, 255));
	shape.setOrigin(shape.getRadius() / 2, shape.getRadius() / 2);
	shape.setOutlineThickness(1);
	shape.setPosition(pos);
}


SnakeCell::~SnakeCell()
{
}

void SnakeCell::update(float deltaTime)
{
	follow();
}
