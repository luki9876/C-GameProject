#include "Physics.h"

#include <iostream>


Physics::Physics()
{
	jumpStates.speedY = 0;
	jumpStates.ifJump = false;
	force = 0;
	jumpStates.gravityDeltaTime = 0;
}

void Physics::InitPhysics(sf::Sprite* l_pointerToSprite, const int* tab, int widthTab, int heightTab, int l_colisionTile, sf::Vector2f l_calibratePositionBottomRightCorner, sf::Vector2f l_speed)
{
	calibratePositionBottomRightCorner = l_calibratePositionBottomRightCorner;
	pointerToSprite = l_pointerToSprite;
	pointerToTable = tab;
	widthColisionTable = widthTab;
	heightColisionTable = heightTab;
	colisionTileFromTable = l_colisionTile;
	speed = l_speed;
}


bool Physics::checkCollision()
{
	for (int i = 0; i < 2; i++)
	{

		if (positionInTile.x < 0 || positionInTile.x > widthColisionTable)
			continue;
		if (positionInTile.y < 0 || positionInTile.y > heightColisionTable)
			continue;
		//gege
		int positionXinTable = (int) (positionInTile.x - 1 + i) + (positionInTile.y) * widthColisionTable;
		if (pointerToTable[positionXinTable] == colisionTileFromTable)
			return true;
	}
	return false;
}

void Physics::setPosition(sf::Vector2f position)	
{ 
	pointerToSprite->setPosition(position);
}

sf::Vector2f Physics::getPositon()	{ return sf::Vector2f(pointerToSprite->getPosition()); }

sf::Vector2f Physics::getPositionInTile()
{
	return sf::Vector2f(positionInTile);
}


void Physics::updatePhysics(sf::Vector2f direction, float l_deltaTime)
{
	deltaTime = l_deltaTime;
	jumpStates.gravityDeltaTime += deltaTime;
	calculatePosition(direction);

	if (!(checkCollision()) || jumpStates.ifJump == true)
	{
		gravity();
	}
	else
		jumpStates.speedY = 0;

	setPosition(ActualPosition);
}




void Physics::calculatePosition(sf::Vector2f direction)
{
	Velocity = speed;
	Velocity.x = direction.x * Velocity.x * deltaTime;
	Velocity.y = direction.y * Velocity.y * deltaTime;

	ActualPosition.y = Velocity.y + getPositon().y;
	ActualPosition.x = Velocity.x + getPositon().x;

	sf::Vector2f m_bottomRight =
		sf::Vector2f(sf::Vector2f(pointerToSprite->getGlobalBounds().left + pointerToSprite->getGlobalBounds().width + calibratePositionBottomRightCorner.x,		//(-27, -11);
			pointerToSprite->getGlobalBounds().top + pointerToSprite->getGlobalBounds().height + calibratePositionBottomRightCorner.y));

	positionInTile.x = int(m_bottomRight.x / 32);
	positionInTile.y = int(m_bottomRight.y / 32);
}

void Physics::gravity()
{

		if (jumpStates.speedY == 0 && jumpStates.ifJump == true)
		{
			jumpStates.oldPositionY = getPositon().y;
			jumpStates.speedY -= force;
			jumpStates.ifJump = false;
		}
		jumpStates.oldSpeedY = jumpStates.speedY;
		jumpStates.speedY += deltaTime * jumpStates.CONST_GRAVITY;
		if (jumpStates.oldSpeedY <= 0 && jumpStates.speedY >= 0)
		{
			jumpStates.gravityDeltaTime = 0;
		}

		ActualPosition.y = getPositon().y +deltaTime * jumpStates.CONST_GRAVITY * jumpStates.speedY;


}

void Physics::jump(float l_force)
{
	if (checkCollision())
	{
		jumpStates.ifJump = true;
	}
	else
	{
		jumpStates.ifJump = false;
	}
	force = l_force;
}




