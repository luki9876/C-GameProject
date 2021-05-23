#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct JumpStates
{
	const float CONST_GRAVITY = 43; // = 1;
	
	float gravityDeltaTime;
	float oldSpeedY;
	float speedY;
	
	int oldPositionY = 0;
	bool ifJump;
};






class Physics
{
public:
	
	Physics();

	void InitPhysics(sf::Sprite* l_pointerToSprite, const int* tab, int widthTab, int heightTab, int l_colisionTile, sf::Vector2f l_calibratePositionBottomRightCorner, sf::Vector2f l_speed);

	bool checkCollision();
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPositon();
	sf::Vector2f getPositionInTile();

	void updatePhysics(sf::Vector2f direction, float l_deltaTime);
	void calculatePosition(sf::Vector2f direction);
	void gravity();

	void jump(float l_force);

private:
	JumpStates jumpStates;
	sf::Vector2f ActualPosition;
	sf::Vector2f positionInTile;
	sf::Vector2f Velocity;
	sf::Vector2f calibratePositionBottomRightCorner;
	sf::Vector2f speed;

	int widthColisionTable;
	int heightColisionTable;
	int colisionTileFromTable;

	float deltaTime;
	float force;
	

	sf::Sprite* pointerToSprite;
	const int* pointerToTable;

};

