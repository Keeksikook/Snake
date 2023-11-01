#include "Snake.h"

bool Snake::hitSelf()
{
	bool hit = 0;
	for (int i = 1; i < cells.size(); i++)
		if (head.distToEntity(*cells[i]) - 2 * 6 <= 0)
			hit = true;
	return hit;
}

bool Snake::touchFood(SnakeFood& food)
{
	return (head.distToEntity(food) - head.getRadius() - food.getRadius() <= 0);
}

bool Snake::hitWall() /*Bot and Right wall not accurate*/
{
	if (head.getPos().x > winSize.x - 2*head.getRadius() 
		|| head.getPos().x < head.getRadius()
		|| head.getPos().y > winSize.y - 2*head.getRadius()
		|| head.getPos().y < head.getRadius())
		return true;
	else return false;
}

Snake::Snake(sf::Vector2<float> pos)
	:
	head(pos)
{
	cells.push_back(new SnakeCell(&head));
	for (int i = 0; i < 1; i++) cells.push_back(new SnakeCell(cells[i]));
//	std::cout << "snake parts size: " << cells.size() + 1 << "\n";

}

Snake::Snake(sf::Vector2<float> pos, sf::Vector2<float> speed)
	:
	head(pos, speed)
{
	cells.push_back(new SnakeCell(&head));
	for (int i = 0; i < 1; i++) cells.push_back(new SnakeCell(cells[i]));
	//std::cout << "snake parts size: " << cells.size() + 1 << "\n";
}

void Snake::update(float deltaTime, std::vector<SnakeFood>& food)
{

	//Die if hit self or wall
	if (hitSelf() || hitWall())
	{
		this->alive = false;
		return;
	}

	//Use brain
	if (brain)
	{
		brain->control();
	}

	head.update(deltaTime);


	//Grow when meet food
	for (int i = 0; i < food.size(); i++)
		if (touchFood(food[i]))
		{
			grow();
			food.erase(food.begin() + i);
		}

	//Update cells
	for (auto& e : cells)
		e->update(deltaTime);
	
}

void Snake::draw(sf::RenderTarget * target) const
{
	head.draw(target);
	for (SnakeCell* cell : cells)
		cell->draw(target);
}

void Brain::control() const
{
	std::vector<double> results;
	net.getResults(results);	//Gather signals from network & control body

	if (results[0] > 0.5f)
		parent->steer((results[0] - 0.5f)*2);
	if (results[1] > 0.5f)
		parent->steer((results[1] - 0.5f) * -2);
}

void Brain::giveSignals(std::vector<double> inputs)
{
	net.feedForward(inputs);
}
