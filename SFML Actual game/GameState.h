#pragma once
#include "State.h"
#include "Snake.h"
#include "BackgroundMngr.h"

struct Score
{
	unsigned nDeaths = 0, nFoodEaten = 0, length = 3,
		b_nFoodEaten = 0, b_length = 0, t_nFoodEaten = 0; /*t_ total; b_ best*/

	void logAndUpdate(){
		system("CLS");
		std::cout << "{-------SCORE-------}\n";
		std::cout << "No of deaths: " << nDeaths << "\n";
		std::cout << "No of food eaten: " << nFoodEaten << "\n";
		std::cout << "Current length: " << length << "\n";
		std::cout << "{-------Best-------}\n";
		std::cout << "No of food eaten: " << b_nFoodEaten << "\n";
		std::cout << "Length: " << b_length << "\n";
		std::cout << "---------------------\n";
		std::cout << "Average food per death: " << ((nDeaths == 0)? (0.f):(float(roundf(float(t_nFoodEaten) / float(nDeaths) * 100.f) / 100.f))) << "\n";
	}
};

class GameState :
	public State
{
private:
	bool paused = false;
	Snake* snake;
	std::vector<SnakeFood> food;
	Score score;
	BackgroundMngr mngr;
public:
	GameState(sf::RenderWindow* window, sf::Event& event);
	virtual ~GameState();

	//Functions

	void endState();
	void updateInput(const float& dt);
	void update(const float& dt);
	void draw(sf::RenderTarget* target = nullptr);
	void pause() { paused = !paused; }
};

