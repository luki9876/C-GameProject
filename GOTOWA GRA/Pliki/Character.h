#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Animation.h"
#include "Physics.h"
#include <vector>

enum class Direction {None, Left, Right};
enum class PlayerHealthState { Live, Dead, CompleteLevel };

struct Points
{
	const float POINTS_FOR_DISTANCE = 0.01;
	const int POINST_FOR_ENEMY = 200;
	
	float score;
	float maximumDistance;
	
};

struct Tile
{
	const int SIZE_TILE_X = 32;
	const int SIZE_TILE_Y = 32;

	int amountTileX;
};



struct PositionInFileDifferentAnimation
{
	sf::Vector2f WalkingAndShooting;
	sf::Vector2f Walking;
	sf::Vector2f Shooting;
	sf::Vector2f Idle;
	sf::Vector2f Dead;

};

struct AmountStatesAnimation
{
	const int WALKING_AND_SHOOTING = 6;
	const int WALKING = 6;
	const int SHOOTING = 8;
	const int IDLE = 1;
	const int DEAD = 4;
};

struct PlayerStates
{
	const float JUMP_FORCE = 15;//0.35;

	const int HEIGHT_TEXTURE_CHARACTER = 94;
	const int WIDTH_TEXTURE_CHARACTER = 80;

	const int RESPAWN_X_VALUE = 310;
	const int RESPAWN_Y_VALUE = 455;

	float timeToShiftAnimation;
	float sumTime;

	int currentFrameAnimation;
	int maximumFrameAnimation;

	bool shoot;
	bool jump;


	sf::Vector2f direction;
	
};

struct BulletStates
{
	const float TIME_TO_MAKE_NEW_BULLETS = 0.5;
	const float CORRECT_POSITION_BULLET_X = 55;
	const float CORRECT_POSITION_BULLET_Y = 35;
	const float RANGE = 440;
	const float SPEED_BULLET = 450;
	const float OFFSET_HIT_PLAYER_X = -45;
	const float OFFSET_HIT_PLAYER_Y = 90;
	float timeElapsedToGenerateNewBullets;
};

struct Health
{
	const sf::Vector2u POSITION = sf::Vector2u(350, 64);
	
	int amountLives;
	std::vector<sf::Sprite> heartVector;
};


class Character
{

public:

	Character();
	int getScore();
	int getTypeEndGame();
	bool isLife();

	void InitCharacter(std::string TexLocation, const int* tab, int l_widthTab, int l_heightTab, sf::Vector2f startPosition, sf::Vector2f l_speed);
	void handleInput(void);
	void Update(float &deltaTime, std::vector<sf::Sprite>& enemyBulletVector, float positionViewX);
	void checkIfHit(std::vector<sf::Sprite>& enemyBulletVector);
	void setAmountLives(int lives);
	void Draw(sf::RenderTarget &window);

	sf::Vector2f getPosition();
	std::vector<sf::Sprite> *getBullets();

private:
	bool ifUnderMap();

	void ifCompleteLevel();
	void generateBullets();
	void updateBullets(float dt);
	void updateDistansPoints();
	void setDirection(Direction l_dir);
	void setAnimation(void);
	void UpdateAnimation(float dTime);
	void updateHeart(float positionView);
	void detectActions();
	void handleActions();

	void walkingAndShooting();
	void walking();
	void shooting();
	void idle();
	void dead();


	sf::Vector2f m_Position;
	sf::Vector2f m_bottomRight;
	sf::Vector2i m_positionInTile;


	bool enableGenerateBullets;


	const int* table;

	int heightTable;
	int widthTable;

	float dTime;

	Direction m_dir;
	std::vector<sf::Sprite> bulletsVector;
	sf::Texture BulletTex;
	sf::Texture heartTex;
	sf::Sprite Bullet;
	sf::Sprite Sprite;
	sf::Sprite heart;
	Physics physics;
	Animation animation;
	sf::RectangleShape rectangle;

	PositionInFileDifferentAnimation positionInFileDifferentAnimation;
	AmountStatesAnimation amountStatesAnimation;
	PlayerStates playerStates;
	BulletStates bulletStates;
	PlayerHealthState playerHealthState;
	Health health;
	Points points;
	Tile tile;
};

