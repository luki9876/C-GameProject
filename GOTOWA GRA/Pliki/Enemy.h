#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "Animation.h"
#include "Physics.h"
#include <iostream>

using namespace std;

//struct PositionInFileDifferentAnimation
//{
//	sf::Vector2f PositionTecture;
//};

enum class HealthState { Dead, Live, Fight };
struct EnemyStatus
{
	const float OFFSET_HEALTH_BAR_X = 0;
	const float OFFSET_HEALTH_BAR_Y = 0;
	const float timeToShiftAnimation = 0.4;//5
	const int heightHealth = 10;
	const float viewRagne = 450;
		
	float timeElapsedToUpdateAnimation;
	int currentFrameAnimation;
	unsigned int valueHealth; 
	

};

struct EnemyMoveStatus
{
	const float maximumDistanceForward = 100;
	const float maximumDistanceBackward = -100;
	sf::Vector2f direction;
	sf::Vector2f startPoint;
};

struct BulletStatus
{
	const float SPEED_BULLETS = -140;
	const float RANGE_BULETS = -380;
};

struct AmountStatesAnimationEnemy
{
	const int maximumFramesForAnimation = 4;
	const int live = 2;
	const int dead = 3;
	const int calm = 0;
};






class Enemy
{

public:
	Enemy();
	void initEnemy(string l_locationTex, const int* l_pointerToTable, int l_widthTable, int l_heightTable ,
		sf::Vector2f l_startPoint, sf::Vector2f l_PositionTecture, sf::Vector2f l_sizeRenderWindow, sf::Vector2f l_speed);

	void Update(float& deltaTime, std::vector<sf::Sprite> &bulletVector, sf::Vector2f playerPositon);
	bool checkIfHit(std::vector<sf::Sprite> &bulletVector);
	void enemyHited();
	void Draw(sf::RenderTarget& window);
	std::vector<sf::Sprite>* enemyGetBullets();
	int ifEnemyLive();


private:
	void enemyMove(float deltaTime);
	void enemyFightAnimation(float& deltaTime);
	void enemyTakeShoots(std::vector<sf::Sprite>& bulletVector);
	void enemyShoot();
	void enemyDeadAnimation();
	void enemyCalmEnemy();
	void enemyLive(float& deltaTime, std::vector<sf::Sprite>& bulletVector, sf::Vector2f playerPositon);
	bool enemyEnableToShoot(sf::Vector2f Pposition);
	void enemyUpdateBullets(float& deltaTime);


	//bool erase_bullets;

	EnemyMoveStatus enemyMoveStatus;
	EnemyStatus enemyStatus;
	HealthState healthState;
	AmountStatesAnimationEnemy amountStatesAnimationEnemy;
	BulletStatus bulletStatus;
	
	bool erase_bullets;
	std::vector<sf::Sprite> enemyBulletVector;
	sf::Texture enemyBulletTex;
	sf::Sprite enemyBullet;
	sf::Sprite enemy;
	sf::RectangleShape *healthBar;
	Animation animation;
	Physics physics;
};

