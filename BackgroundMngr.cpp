#include "BackgroundMngr.h"
#include <fstream>
#include <iostream>
void BackgroundMngr::readFile(const char* folder)
{
	std::ifstream ifs(folder + (std::string)"/keys.txt");
	if (!ifs.is_open())
	{
		perror("backgroundmngr ifstream failed");
	}
	else
	{
		if (backgrounds.size())
		{
			for (auto& a : backgrounds)
			{
				delete a.second;
			}
			backgrounds.clear();
		}

		std::string path, key;
		while (ifs >> path >> key)						
		{
			sf::Texture* img = new sf::Texture;
			img->loadFromFile(folder + std::string("/") + path);
			backgrounds[key] = img;
			path.clear();
			key.clear();
		}											
	}
}
sf::Image& BackgroundMngr::makeImage(const sf::Color& color)
{
	sf::Image img;
	img.create(window.getSize().x, window.getSize().y, color);
	return img;
}
void BackgroundMngr::updateScale()
{
	auto targetSize = window.getView().getSize();
	drawingTool.setScale(
		targetSize.x / drawingTool.getLocalBounds().width,
		targetSize.y / drawingTool.getLocalBounds().height);
}
void BackgroundMngr::update(float dt)
{
	if (a_toEnd.asMilliseconds() > 0)
	{
		a_toEnd -= sf::seconds(dt);
	}
	if (a_toEnd < sf::seconds(0))
		a_toEnd = sf::seconds(0);
}
BackgroundMngr::BackgroundMngr(sf::RenderWindow& window, const char* folder)
	:
	window(window),
	drawingTool()
{

	readFile(folder);
}

BackgroundMngr::BackgroundMngr(sf::RenderWindow& window, const char* folder, const char* backgroundtype)
	:
	BackgroundMngr(window, folder)
{
	front = backgrounds[(std::string)backgroundtype];
}

void BackgroundMngr::setImage(const char * key)
{
	front = backgrounds[key];
	drawingTool.setTexture(*front);
	updateScale();
}

void BackgroundMngr::animate(const char * key1, const char * key2, float time)
{
	front = backgrounds[key1];
	back = backgrounds[key2];
	a_total = sf::seconds(time);
	a_toEnd = sf::seconds(time);
}

void BackgroundMngr::fadeOut(float time)
{
	back = blacktxtr;
	a_total = sf::seconds(time);
	a_toEnd = sf::seconds(time);
}

