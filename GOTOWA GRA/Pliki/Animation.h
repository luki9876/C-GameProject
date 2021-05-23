#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>



class Animation
{

public:
	Animation();
	void setSizeRenderWindow(sf::Vector2f size);
	void setPositionTecture(sf::Vector2f sizeTex);


	void setTexture(sf::Sprite& l_sprite, std::string TexLocation);
	void setAnimations(sf::Sprite& l_sprite, int& iterator);

	void updateRenderWindow(int amount_tex);


private:
	
	sf::IntRect frames[8];
	sf::Texture texture;

	sf::Vector2f m_PositionTexture;
	sf::Vector2f m_sizeRenderWindow;
	
};

