#pragma once
#include<SFML/Graphics.hpp>
class Entity
{
	
protected:
	sf::Vector2<float> pos, speed;
public:
	Entity(sf::Vector2<float> pos, sf::Vector2<float> speed) :
		pos(pos),
		speed(speed)
	{}
	Entity(sf::Vector2<float> pos) :
		pos(pos),
		speed({0, 0})
	{}
	virtual ~Entity();
	virtual void update(float deltaTime);
	void draw(sf::RenderTarget* target, sf::Color color);
	virtual sf::Vector2<float> getPos() const  { return pos; }
	virtual sf::Vector2<float> getSpeed() const { return pos; }
};

