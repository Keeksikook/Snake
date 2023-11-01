#pragma once
#include"GameState.h"

class Game
{
private:

	//Variables

	sf::RenderWindow* window;
	sf::Event SFEvent;
	sf::Clock dtClock;
	float dt = 0;
	std::stack<State*> states;

	//Initialization

	void initWin();

	//Functions

	void updateDt();
	void initStates();

public:

	//Constructor & Destructor

	Game();
	virtual ~Game();

	//Functions

	void updateSFEvents();
	void update();
	void draw();
	void run();
};