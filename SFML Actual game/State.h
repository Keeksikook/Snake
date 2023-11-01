#pragma once
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<fstream>
#include<sstream>
#include<stack>
#include<vector>
#include<assert.h>
#include<iostream>
#include"Entity.h"


namespace vec
{
	template<typename T>
	float lenght(const sf::Vector2<T>& source)
	{
		return sqrtf(source.x * source.x + source.y * source.y);
	}
	template<typename T>
	float lenght(const T& x, const T& y) { return lenght(sf::Vector2<T>{x, y}); }
	template<typename T>
	sf::Vector2<T> normalize(const sf::Vector2<T>& source)
	{
		float length = lenght(source);
		if (length != 0)
			return sf::Vector2<T>(source.x / length, source.y / length);
		else
			return source;
	}
	template<typename T>
	void printVec(sf::Vector2<T> vector) {
		std::cout << vector.x << ", " << vector.y;
	}
	template<typename T>
	void printVecB(sf::Vector2<T> vector) {
		std::cout << "{ "; printVec(vector); std::cout << " }";
	}

	template<typename T, typename T2>
	sf::Vector2<T>& operator-=(sf::Vector2<T>& vector, T2 subtractative) {
		vector -= vec::normalize(vector) * subtractative;
		return vector;
	}

}


class State
{
private:

protected:
	sf::RenderWindow* window;
	sf::Event& event;
	bool quit = false;
	bool paused = false;
public:
	State(sf::RenderWindow* window, sf::Event& event);
	virtual ~State();

	virtual void checkQuit();
	virtual void endState() = 0;
	const bool& getQuit() const;
	virtual void update(const float& dt) = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void draw(sf::RenderTarget* target = nullptr) = 0;
	void pause() { paused = !paused; }
};

