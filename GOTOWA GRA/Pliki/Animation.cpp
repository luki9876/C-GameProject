#include "Animation.h"
#include <iostream>




Animation::Animation()
{
}

void Animation::setSizeRenderWindow(sf::Vector2f size)
{
	m_sizeRenderWindow = size;
}

void Animation::setPositionTecture(sf::Vector2f sizeTex)
{
	m_PositionTexture = sizeTex;
}



void Animation::setTexture(sf::Sprite& l_sprite, std::string TexLocation)
{
	if (!(texture.loadFromFile(TexLocation)))		///	"texture/hero.png"
	{
		std::cout << "nie udalo sie zaladowac tekstury";
	}
	l_sprite.setTexture(texture);


}

void Animation::setAnimations(sf::Sprite& l_sprite, int &iterator)
{
	l_sprite.setTextureRect(frames[iterator]);
//	std::cout << iterator << "\n";
}


void Animation::updateRenderWindow(int amount_tex)
{
	for (int i = 0; i < amount_tex; i++)
	{
		frames[i] = { i * int(m_PositionTexture.x) , int(m_PositionTexture.y), int(m_sizeRenderWindow.x), int(m_sizeRenderWindow.y) };

	}
}
