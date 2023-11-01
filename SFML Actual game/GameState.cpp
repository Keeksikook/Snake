#include "GameState.h"
constexpr auto r = 10;

GameState::GameState(sf::RenderWindow* window, sf::Event& event)
	:
	State(window, event),
	snake(new Snake({ 100, 300 }, { 80, 0 })),
	mngr(*window, "Backgrounds", "lines")
{
	food.emplace_back(SnakeFood({ 400, 300 }, r));
}

GameState::~GameState()
{
	endState();
}

void GameState::endState()
{
}

void GameState::updateInput(const float & dt)
{
	checkQuit();
}

void GameState::update(const float& dt)
{
	if (!paused) 
	{
		mngr.update(dt);
		if (food.size() == 0)
		{
			food.emplace_back(sf::Vector2<float>{ float((rand() % (window->getSize().x - 100)) + 50), float((rand() % (window->getSize().y - 100)) + 50)}, r);
			score.nFoodEaten++;
			score.t_nFoodEaten++;
			score.length++;
			while (score.b_length < score.length)
				score.b_length++;
			while (score.b_nFoodEaten < score.nFoodEaten)
				score.b_nFoodEaten++;
			//score.logAndUpdate();
			mngr.animate("lines", "cotton", 6.f);
		}

		updateInput(dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			snake->steer(-2.5*dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			snake->steer(2.5*dt);
		if (event.type == sf::Event::Resized)
		{
			snake->showWindow(window->getSize());
			mngr.updateScale();
			food.clear();
			food.emplace_back(sf::Vector2<float>{ float((rand() % (window->getSize().x - 100)) + 50), float((rand() % (window->getSize().y - 100)) + 50)}, r);
			
		}
		snake->update(dt, food);
		if (!snake->isAlive())
		{
			delete snake;
			snake = new Snake({ 100, 300 }, { 80, 0 });
			snake->showWindow(window->getSize());
			score.length = 3;
			score.nFoodEaten = 0;
			score.nDeaths++;
			//score.logAndUpdate();
			mngr.animate("cotton", "lines", 6.f);
		}
		for (auto& f : food)
			f.update(dt);
	}
}

void GameState::draw(sf::RenderTarget* target)
{
	mngr.draw();
	if (!target)
		target = window;
	snake->draw(target);
	for (auto& f : food)
		f.draw(target);

}

