#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


class BackgroundMngr
{
private:
	std::map<std::string, sf::Texture*> backgrounds;
	sf::Texture* back = nullptr, *front = nullptr; // back is for animations
	sf::RenderWindow& window;
	sf::Texture* blacktxtr;
	sf::Sprite drawingTool;
	sf::Time a_toEnd, a_total; // animation time til ending and total animation time

	void readFile(const char* filepath);
	sf::Image& makeImage(const sf::Color& color);
public:
	BackgroundMngr(sf::RenderWindow& window, const char* folder);
	BackgroundMngr(sf::RenderWindow& window, const char* folder, const char* backgroundtype);
	~BackgroundMngr() {
		if (backgrounds.size())
		{
			for (auto& a : backgrounds)
			{
				delete a.second;
			}
		}
	}

	void setImage(const char* key);
	void animate(const char* key1, const char* key2, float time);
	void fadeOut(float time);
	void draw()
	{
		if (back)
			drawingTool.setTexture(*back); window.draw(drawingTool);

		if (a_toEnd.asSeconds() > 0) // if ongoing animation...
		{
			float progress = (((float)a_total.asMilliseconds() - (float)a_toEnd.asMilliseconds()) / (float)a_total.asMilliseconds());
			//std::cout << "255 * progress : " << 255 * progress << ",Progress : " << progress << "\n";
			drawingTool.setColor(sf::Color(255, 255, 255, 255 * progress));
		}
		else
			drawingTool.setColor(sf::Color(255, 255, 255, 255));
			
		if (front)
			drawingTool.setTexture(*front); window.draw(drawingTool);

		drawingTool.setColor(sf::Color(255, 255, 255, 255));
	}

	void updateScale();
	void update(float dt);
};

