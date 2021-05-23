#include "Map.h"



bool Map::DrawMap(string l_sMapPath, int l_iSizeTileX, int l_iSizeTileY, const int *l_cBitMap, int l_iSizeBitMapX, int l_iSizeBitMapY)
{
	m_sMapPath = l_sMapPath;
	m_iSizeTileX = l_iSizeTileX;
	m_iSizeTileY = l_iSizeTileY;
	m_iSizeBitMapX = l_iSizeBitMapX;
	m_iSizeBitMapY = l_iSizeBitMapY;

	if (!(m_MapTex.loadFromFile(m_sMapPath)))
	{
		cout << "Error load map";
		return false;
	}

	const int fourVertexPerQuad = 4;
	m_VertexArray.setPrimitiveType(sf::Quads);
	m_VertexArray.resize(m_iSizeBitMapX * m_iSizeBitMapY * fourVertexPerQuad);

	for (int y = 0; y < m_iSizeBitMapY; y++)
	{
		for (int x = 0; x < m_iSizeBitMapX; x++)
		{
			int bitMapNumber = (l_iSizeBitMapX * y + x);
			
			//int actualTileFromTexX = (m_MapTex.getSize().x / m_iSizeTileX);

			sf::Vertex* quad = &m_VertexArray[bitMapNumber * 4] ;
			

			quad[0].position = sf::Vector2f(x * m_iSizeTileX, y*m_iSizeTileY);
			quad[1].position = sf::Vector2f((x + 1) * m_iSizeTileX, y * m_iSizeTileY);
			quad[2].position = sf::Vector2f((x + 1) * m_iSizeTileX, (y + 1) * m_iSizeTileY );
			quad[3].position = sf::Vector2f(x * m_iSizeTileX, (y + 1) * m_iSizeTileY);

			int Ycord =  l_cBitMap[bitMapNumber] / (m_MapTex.getSize().x/m_iSizeTileX) ;
			int Xcord = l_cBitMap[bitMapNumber] % (m_MapTex.getSize().x / m_iSizeTileX);

			quad[0].texCoords = sf::Vector2f(m_iSizeTileX * Xcord, m_iSizeTileY * Ycord);
			quad[1].texCoords = sf::Vector2f(m_iSizeTileX * (Xcord + 1), m_iSizeTileY * Ycord);
			quad[2].texCoords = sf::Vector2f(m_iSizeTileX * (Xcord + 1), m_iSizeTileY * (Ycord+1));
			quad[3].texCoords = sf::Vector2f(m_iSizeTileX * Xcord, m_iSizeTileY * (Ycord + 1));


		}
	}
	return true;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_MapTex;
	target.draw(m_VertexArray, states);
}
