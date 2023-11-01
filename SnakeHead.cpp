#include "Snake.h"



float SnakeHead::distToEntity(Entity & e) const
{
	return vec::lenght(this->getPos() - e.getPos());
}

SnakeHead::SnakeHead(sf::Vector2<float> pos)
	:
	Entity(pos)
{
	shape.setRadius(5);
	shape.setFillColor(sf::Color(255, 0, 0, 255));
	shape.setOrigin(shape.getRadius() / 2, shape.getRadius() / 2);
	shape.setOutlineThickness(1);
	shape.setPosition(pos);
}


SnakeHead::SnakeHead(sf::Vector2<float> pos, sf::Vector2<float> speed)
	:
	Entity(pos, speed)
{
	shape.setRadius(5);
	shape.setFillColor(sf::Color(255, 0, 0, 255));
	shape.setOrigin(shape.getRadius() / 2, shape.getRadius() / 2);
	shape.setOutlineThickness(1);
	shape.setPosition(pos);
}

SnakeHead::SnakeHead(Entity * e)
	:
	Entity(*e)
{
	shape.setRadius(5);
	shape.setFillColor(sf::Color(255, 0, 0, 255));
	shape.setOrigin(shape.getRadius() / 2, shape.getRadius() / 2);
	shape.setOutlineThickness(1);
	shape.setPosition(pos);
}

void SnakeHead::update(float deltaTime)
{
	Entity::update(deltaTime);
	shape.setPosition(pos);
}

void SnakeHead::steer(float angle)
{
	float originalLenght = vec::lenght(speed.x, speed.y);
	float originalAngle;
	if(speed.x != 0)
		originalAngle = atan2f(speed.y, speed.x);
	else 
		originalAngle = atan2f(speed.y , 0.000001);
	float newAngle = originalAngle + angle;
	this->speed = sf::Vector2<float>{ cosf(newAngle) * originalLenght, sinf(newAngle) * originalLenght };
}
SnakeHead::~SnakeHead()
{
}
