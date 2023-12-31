#include "Game.h"

//Static functions

//Initializer functions

void Game::initWin()
{
	
	std::ifstream ifs("Config/window.ini");
	//VS launch dir is different from other
	if (!ifs.is_open())
	{
		perror("failed regular launch dir");
		ifs.open("window.ini");
	}
	if (!ifs.is_open())
	{
		perror("failed VS launch dir");
	}
	
	std::string title("A game of snake");
	sf::VideoMode vidMode(800, 600);
	bool vSyncOn = 1;
	short frameRateLimit = 90;

	if(ifs.is_open())
	{
		ifs >> frameRateLimit;
		ifs >> vidMode.width;
		ifs >> vidMode.height;
		ifs >> vSyncOn;
	}

	this->window = new sf::RenderWindow(vidMode, title);
	window->setFramerateLimit(frameRateLimit);
	window->setVerticalSyncEnabled(vSyncOn);
	ifs.close();
	
}

//Consturctor & Destructor

Game::Game()
{
	initWin();
	initStates();
}

Game::~Game()
{
	delete this->window;
	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
		
}

//Functions

void Game::updateSFEvents()
{
	while (window->pollEvent(SFEvent))
	{
		if (SFEvent.type == sf::Event::Closed)
			window->close();
		if (SFEvent.type == sf::Event::Resized)
		{
			sf::FloatRect view(0, 0, SFEvent.size.width, SFEvent.size.height);
			window->setView(sf::View(view));
		}
		if (SFEvent.type == sf::Event::KeyPressed)
		{
			if (SFEvent.key.code == sf::Keyboard::P)
			{
				states.top()->pause();
			}
		}
	}
}

void Game::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Game::initStates()
{
	states.push(new GameState(window, SFEvent));
}

void Game::update()
{
	updateSFEvents();
	if (!states.empty())
	{
		states.top()->update(dt);
		if (states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
		else
		{
			states.top()->update(dt);
		}
	}
	else
	{
		this->window->close();
	}
		

}

void Game::draw()
{
	window->clear();
	if (!states.empty())
		states.top()->draw(window);
	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		updateDt();
		update();
		draw();
	}
}
