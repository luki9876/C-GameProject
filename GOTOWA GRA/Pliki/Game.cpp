#include "Game.h"






Game::Game()
{
	stateGame = StateGame::MainMenu;
}

void Game::init(sf::RenderTarget &window)
{
	dimensionWindow = window.getSize();
	menu.createMenu(window.getSize());
}



	

void Game::update(float deltaTime, const int* collisionAndRenderMap, sf::RenderTarget& window)
{

	if (menu.ifEnableInitGame(deltaTime) && (stateGame == StateGame::MainMenu) )
	{
		initWorld(deltaTime, collisionAndRenderMap, window);
		stateGame = StateGame::Running;
	}


	if (stateGame == StateGame::Running)
	{
		if (player.isLife())
		{
			player.checkIfHit(*enemyTank2.enemyGetBullets());
			player.checkIfHit(*enemyTank3.enemyGetBullets());
			player.checkIfHit(*enemyTank4.enemyGetBullets());
			player.checkIfHit(*enemyTank5.enemyGetBullets());
			player.checkIfHit(*enemyTank6.enemyGetBullets());
			player.checkIfHit(*enemyTank7.enemyGetBullets());
			player.checkIfHit(*enemyTank8.enemyGetBullets());
			player.Update(deltaTime, *enemyTank1.enemyGetBullets(), view.getCenter().x);
			
			enemyTank1.Update(deltaTime, *player.getBullets(), player.getPosition());
			enemyTank2.Update(deltaTime, *player.getBullets(), player.getPosition());
			enemyTank3.Update(deltaTime, *player.getBullets(), player.getPosition());
			enemyTank4.Update(deltaTime, *player.getBullets(), player.getPosition());
			enemyTank5.Update(deltaTime, *player.getBullets(), player.getPosition());
			enemyTank6.Update(deltaTime, *player.getBullets(), player.getPosition());
			enemyTank7.Update(deltaTime, *player.getBullets(), player.getPosition());
			enemyTank8.Update(deltaTime, *player.getBullets(), player.getPosition());

			updateView(deltaTime);
		}
		else
		{
			int TypeEndGame = player.getTypeEndGame();
			if (TypeEndGame  == 1)
			{
				stateGame = StateGame::Dead;
				menu.setStateDead();
			}
			else if (TypeEndGame == 2)
			{
				stateGame = StateGame::End;
				menu.setStateEnd();
			}
			menu.calculateResult( (float)(player.getScore()  + calculatePointsForKills()) / difficult);
		}
	}
}

void Game::initWorld(float deltaTime, const int* collisionAndRenderMap, sf::RenderTarget& window)
{
	if (!(mapa.DrawMap(LOCATION_TILE_FOR_MAP_TEXTURE, SIZE_TILEX, SIZE_TILEY, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE)))
	{
		cout << "Error render map";
	}


	view.setCenter(dimensionWindow.x / 2, dimensionWindow.y / 2);
	view.setSize(dimensionWindow.x, dimensionWindow.y);

	difficult = menu.getDifficult();
	player.setAmountLives(difficult);

	player.InitCharacter(LOCATION_PLAYER_TEXTURE, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE, START_PLAYER_POSITION, PLAYER_SPEED);

	enemyTank1.initEnemy(LOCATION_ENEMY_TEXTURE, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE,
		START_ENEMY_TANK_POSITION, TANK_POSITION_IN_FILE, TANK_SIZE_IN_FILE, ENEMY_TANK_SPEED);

	enemyTank2.initEnemy(LOCATION_ENEMY_TEXTURE, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE,
		START_ENEMY_TANK_POSITION2, TANK_POSITION_IN_FILE, TANK_SIZE_IN_FILE, ENEMY_TANK_SPEED);

	enemyTank3.initEnemy(LOCATION_ENEMY_TEXTURE, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE,
		START_ENEMY_TANK_POSITION3, TANK_POSITION_IN_FILE, TANK_SIZE_IN_FILE, ENEMY_TANK_SPEED);

	enemyTank4.initEnemy(LOCATION_ENEMY_TEXTURE, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE,
		START_ENEMY_TANK_POSITION4, TANK_POSITION_IN_FILE, TANK_SIZE_IN_FILE, ENEMY_TANK_SPEED);

	enemyTank5.initEnemy(LOCATION_ENEMY_TEXTURE, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE,
		START_ENEMY_TANK_POSITION5, TANK_POSITION_IN_FILE, TANK_SIZE_IN_FILE, ENEMY_TANK_SPEED);

	enemyTank6.initEnemy(LOCATION_ENEMY_TEXTURE, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE,
		START_ENEMY_TANK_POSITION6, TANK_POSITION_IN_FILE, TANK_SIZE_IN_FILE, ENEMY_TANK_SPEED);

	enemyTank7.initEnemy(LOCATION_ENEMY_TEXTURE, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE,
		START_ENEMY_TANK_POSITION7, TANK_POSITION_IN_FILE, TANK_SIZE_IN_FILE, ENEMY_TANK_SPEED);

	enemyTank8.initEnemy(LOCATION_ENEMY_TEXTURE, collisionAndRenderMap, WIDTH_TABLE, HEIGHT_TABLE,
		START_ENEMY_TANK_POSITION8, TANK_POSITION_IN_FILE, TANK_SIZE_IN_FILE, ENEMY_TANK_SPEED);


}











void Game::updateView(float dtTime)
{
	if (player.getPosition().x > view.getCenter().x + 0)	//32
		view.move(PLAYER_SPEED.x * dtTime,0);
	if (player.getPosition().x < view.getCenter().x - 32-93)
		view.move(-PLAYER_SPEED.x * dtTime, 0);
}

int Game::calculatePointsForKills()
{

	sumPointsForKill = enemyTank1.ifEnemyLive();
	sumPointsForKill += enemyTank2.ifEnemyLive();
	sumPointsForKill += enemyTank3.ifEnemyLive();
	sumPointsForKill += enemyTank4.ifEnemyLive();
	sumPointsForKill += enemyTank5.ifEnemyLive();
	sumPointsForKill += enemyTank6.ifEnemyLive();
	sumPointsForKill += enemyTank7.ifEnemyLive();
	sumPointsForKill += enemyTank8.ifEnemyLive();
	return sumPointsForKill * POINTS_FOR_KILL_TANKS;
}





void Game::drawContent(sf::RenderTarget& l_window)
{

	if (stateGame == StateGame::MainMenu || stateGame == StateGame::End || stateGame == StateGame::Dead)
	{
		view.setCenter(dimensionWindow.x / 2, dimensionWindow.y / 2);
		view.setSize(dimensionWindow.x, dimensionWindow.y);
		l_window.setView(view);
		menu.draw(l_window);	
	}
	else if (stateGame == StateGame::Running)
	{
		l_window.draw(mapa);

		enemyTank1.Draw(l_window);
		enemyTank2.Draw(l_window);
		enemyTank3.Draw(l_window);
		enemyTank4.Draw(l_window);
		enemyTank5.Draw(l_window);
		enemyTank6.Draw(l_window);
		enemyTank7.Draw(l_window);
		enemyTank8.Draw(l_window);

		player.Draw(l_window);
		l_window.setView(view);
	}

}

