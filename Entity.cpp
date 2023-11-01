#include "Entity.h"

Entity::~Entity()
{
}

void Entity::update(float deltaTime)
{
	float& dt = deltaTime;
	pos += {speed.x * dt, speed.y * dt};
}

void Entity::draw(sf::RenderTarget * target, sf::Color color)
{
	sf::Vertex point(pos);
	sf::VertexArray array(sf::Points);
	point.color = color;
	array.append(point);
	
	target->draw(array);
}
