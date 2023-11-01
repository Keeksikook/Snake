#pragma once
#include "State.h"
#include "Network.h"
class SnakeHead :
	public Entity
{
private:
	sf::CircleShape shape;
protected:

public:
	SnakeHead(sf::Vector2<float> pos);
	SnakeHead(sf::Vector2<float> pos, sf::Vector2<float> speed);
	SnakeHead(Entity* e);
	~SnakeHead();

	void draw(sf::RenderTarget* target) const { target->draw(shape); }
	void update(float deltaTime)override;
	void steer(float angle); 
	float distToEntity(Entity& e) const;
	float getRadius() const { return shape.getRadius(); }
	virtual sf::Vector2<float> getPos() const override { return pos; }
	sf::Vector2<float>& getSpeed() { return speed; }
};

class SnakeCell :
	public Entity
{
private:
	Entity* followTarget;
	sf::CircleShape  shape;
	void follow();
public:
	SnakeCell(Entity* followTarget);
	virtual ~SnakeCell();
	void update(float deltaTime)override;
	void draw(sf::RenderTarget* target) const { target->draw(shape); }
	const float getRadius() const { return shape.getRadius(); }
	const sf::Color& getColor() const { return shape.getFillColor(); }
	virtual sf::Vector2<float> getPos() const override { return pos; }
	sf::Vector2<float> getSpeed() const { return speed; }
};

class SnakeFood :
	public Entity
{
private:
	static unsigned long nCreated, nAlive;
	sf::CircleShape shape;
public:
	SnakeFood(sf::Vector2<float> pos, float radius);
	~SnakeFood();
	void draw(sf::RenderTarget* target) const { target->draw(shape); }
	const float getRadius() const { return shape.getRadius(); }
	static unsigned long getnCreated() { return nCreated; }
};

class Snake;

struct Brain
{
	NN::Net net;
	bool active = true;
	Brain(std::vector<unsigned int>& topology, Snake* parent) : net(topology), parent(parent) {}
	void control() const;
private:
	void giveSignals(std::vector<double> inputs);
	void respond() { control(); }
	Snake* parent = nullptr;
};

class Snake
{
private:
	SnakeHead head;
	std::vector<SnakeCell*> cells;
	sf::Vector2<unsigned> winSize = { 800, 600 };
	Brain* brain = nullptr;
	bool hitSelf();
	bool touchFood(SnakeFood& food);
	bool hitWall();
	bool alive = true;
public:
	void showWindow(const sf::Vector2<unsigned>& windowsize) { winSize = windowsize; }
	const bool isAlive() const { return alive; }
	Snake(sf::Vector2<float> pos);
	Snake(sf::Vector2<float> pos, sf::Vector2<float> speed);
	~Snake() { if (brain) unBrain(); }
	void update(float deltaTime, std::vector<SnakeFood>& food);
	void draw(sf::RenderTarget* target) const;
	void steer(float angle) { head.steer(angle); }
	void grow() { cells.push_back(new SnakeCell(cells.back())); }
	void giveBrain(std::vector<unsigned int>& topology) { this->brain = new Brain(topology, this); }
	void unBrain() { delete brain; brain = nullptr; }
	const SnakeHead& getHead() const { return head; }
};