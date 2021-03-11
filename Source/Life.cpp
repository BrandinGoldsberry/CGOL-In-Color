#include <Life.hpp>

Life::Life()
{
	this->alive = false;
	this->life_color = sf::Color(255, 255, 255, 255);
}

Life::~Life()
{
}

void Life::SetRGB(uint8_t R, uint8_t G, uint8_t B)
{
	this->life_color = sf::Color(R, G, B, 255);
}

void Life::SetRGB(sf::Color RGB)
{
	this->life_color = RGB;
}

sf::Color Life::GetColor()
{
	return this->life_color;
}

bool Life::isAlive()
{
	return this->alive;
}

void Life::setAlive(bool isAlive)
{
	this->alive = isAlive;
}
