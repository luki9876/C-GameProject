#pragma once

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

class Map : public sf::Drawable, public sf::Transformable
{
public:
	bool DrawMap(string l_sMapPath, int l_iSizeTileX, int l_iSizeTileY, const int *l_cBitMap, int l_iSizeBitMapX, int l_iSizeBitMapY);


private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	string m_sMapPath;
	int m_iSizeTileX;
	int	m_iSizeTileY;
	int m_iSizeBitMapX;
	int m_iSizeBitMapY;
	sf::Texture m_MapTex;
	sf::VertexArray m_VertexArray;



};

