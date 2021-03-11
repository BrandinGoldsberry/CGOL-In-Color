#pragma once
#include <cstdint>
#include <SFML/Graphics.hpp>

class Life
{
public:
	Life();
	~Life();
	void SetRGB(uint8_t R, uint8_t G, uint8_t B);
	void SetRGB(sf::Color RGB);
	void setAlive(bool isAlive);
	bool isAlive();
	
	sf::Color GetColor();
private:
	bool alive;
	sf::Color life_color;
};