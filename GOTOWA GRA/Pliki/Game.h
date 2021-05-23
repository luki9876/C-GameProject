#pragma once
#include "Character.h"
#include "Map.h"
#include "Enemy.h"
#include "Menu.h"

enum class StateGame { MainMenu, Running, Dead, End };
enum class Difficult { Easy = 1, Medium, Hard };


class Game
{
public:
	
	Game();
	void init(sf::RenderTarget& window);

	void update(float deltaTime, const int* collisionAndRenderMap, sf::RenderTarget& window);
	void drawContent(sf::RenderTarget& l_window);
	void initWorld(float deltaTime, const int* collisionAndRenderMap, sf::RenderTarget& window);

private:
	void updateView(float dtTime);
	int calculatePointsForKills();
	bool game_enabled;
	sf::Vector2u dimensionWindow;
	int difficult;
	int sumPointsForKill;
	const int POINTS_FOR_KILL_TANKS = 300;
	//---------------------------MAP PARAMETERS-------------------------------------------------------------------
	const int WIDTH_TABLE = 208; // 52
	const int HEIGHT_TABLE = 16;
	const int SIZE_TILEX = 32;
	const int SIZE_TILEY = 32;


	//--------------------------TEXTURE LOCATIONS-----------------------------------------------------------------
	const string LOCATION_TILE_FOR_MAP_TEXTURE = "texture/tile1.png";
	const string LOCATION_PLAYER_TEXTURE = "texture/hero.png";
	const string LOCATION_ENEMY_TEXTURE = "texture/creatures1.png";


	//--------------------------POSITION IN TEXTURE ENEMIES------------------------------------------------------
	//						 ###### TANK ####
	const sf::Vector2f TANK_POSITION_IN_FILE = sf::Vector2f(32, 32); 
	const sf::Vector2f TANK_SIZE_IN_FILE = sf::Vector2f(32, 32);


	//--------------------------START POSITIONS-------------------------------------------------------------------
	const sf::Vector2f START_PLAYER_POSITION = sf::Vector2f(30, 200);
	const sf::Vector2f START_ENEMY_TANK_POSITION = sf::Vector2f(600, 200);
	const sf::Vector2f START_ENEMY_TANK_POSITION2  = sf::Vector2f(950, 200);
	const sf::Vector2f START_ENEMY_TANK_POSITION3 = sf::Vector2f(1850, 200);
	const sf::Vector2f START_ENEMY_TANK_POSITION4 = sf::Vector2f(2300, 200);
	const sf::Vector2f START_ENEMY_TANK_POSITION5 = sf::Vector2f(3150, 200);	//git
	const sf::Vector2f START_ENEMY_TANK_POSITION6 = sf::Vector2f(4400, 200);
	const sf::Vector2f START_ENEMY_TANK_POSITION7 = sf::Vector2f(5300, 200);	//git
	const sf::Vector2f START_ENEMY_TANK_POSITION8 = sf::Vector2f(5650, 200);



	//--------------------------SPEEDS-----------------------------------------------------------------------------
	const sf::Vector2f PLAYER_SPEED = sf::Vector2f(200, 200);
	const sf::Vector2f ENEMY_TANK_SPEED = sf::Vector2f(60, 50);
	
	StateGame stateGame;
	Menu menu;
	Map mapa;
	Character player;
	Enemy enemyTank1;
	Enemy enemyTank2;
	Enemy enemyTank3;
	Enemy enemyTank4;
	Enemy enemyTank5;
	Enemy enemyTank6;
	Enemy enemyTank7;
	Enemy enemyTank8;
	sf::View view;


};

