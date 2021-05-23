#include "Enemy.h"



Enemy::Enemy()
{
	enemyStatus.currentFrameAnimation = 0;
	healthState = HealthState::Live;
	if (!enemyBulletTex.loadFromFile("texture/bullet_rifleL.png"))
	{
		std::cout << "nie udalo sie zaladowac pocisku czolgu";
	}
	enemyBullet.setTexture(enemyBulletTex);
	enemyBullet.setScale(0.07, 0.07);
	erase_bullets = true;
}

void Enemy::initEnemy(string l_locationTex, const int* l_pointerToTable, int l_widthTable, int l_heightTable,
	sf::Vector2f l_startPoint, sf::Vector2f l_PositionTecture, sf::Vector2f l_sizeRenderWindow, sf::Vector2f l_speed)
{
	animation.setTexture(enemy, l_locationTex);
	animation.setPositionTecture(l_PositionTecture);
	animation.setSizeRenderWindow(l_sizeRenderWindow);
	animation.updateRenderWindow(amountStatesAnimationEnemy.maximumFramesForAnimation);

	enemy.setScale(sf::Vector2f(4, 4));
	physics.InitPhysics(&enemy, l_pointerToTable, l_widthTable, l_heightTable, 1, sf::Vector2f(-15,-12), sf::Vector2f (l_speed) );
	
	healthBar = new sf::RectangleShape;
	healthBar->setFillColor(sf::Color::Red);
	enemyStatus.valueHealth = 140;
	physics.setPosition(sf::Vector2f(l_startPoint));
	healthBar->setSize(sf::Vector2f(enemyStatus.valueHealth, enemyStatus.heightHealth));
	healthBar->setPosition(enemy.getPosition().x + enemyStatus.OFFSET_HEALTH_BAR_X, enemy.getPosition().y + enemyStatus.OFFSET_HEALTH_BAR_Y);
	enemyMoveStatus.direction = sf::Vector2f(1, 0);
	
	enemyMoveStatus.startPoint = l_startPoint;
}

void Enemy::Update(float& deltaTime, std::vector<sf::Sprite> &bulletVector, sf::Vector2f playerPositon)
{
	if (healthState == HealthState::Live)
	{
		enemyLive(deltaTime, bulletVector, playerPositon);
		enemyUpdateBullets(deltaTime);
		enemyMove(deltaTime);
	}
	else
	{
		enemyDeadAnimation();
	}

}

void Enemy::enemyLive(float& deltaTime, std::vector<sf::Sprite>& bulletVector, sf::Vector2f playerPositon)
{

	enemyTakeShoots(bulletVector);

	if (enemyEnableToShoot(playerPositon))
	{
		enemyFightAnimation(deltaTime);
	}
	else
	{
		enemyCalmEnemy();
	}
}

bool Enemy::enemyEnableToShoot(sf::Vector2f Pposition)
{
	if (physics.getPositon().x - enemyStatus.viewRagne < Pposition.x)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::enemyUpdateBullets(float& deltaTime)
{
	for (int i = 0; i < enemyBulletVector.size(); i++)
	{
		enemyBulletVector[i].move(bulletStatus.SPEED_BULLETS *deltaTime, 0.f);
	}
	for (int i = 0; i < enemyBulletVector.size(); i++)
	{
		if (enemyBulletVector[i].getPosition().x < physics.getPositon().x + bulletStatus.RANGE_BULETS)
		{
			enemyBulletVector.erase(enemyBulletVector.begin() + i);
		}
	}
}


void Enemy::enemyDeadAnimation()
{
	if (erase_bullets)
	{
		erase_bullets = false;
		enemyBulletVector.clear();
	
	}
	enemyStatus.currentFrameAnimation = amountStatesAnimationEnemy.dead;
	animation.setAnimations(enemy, enemyStatus.currentFrameAnimation);
}

void Enemy::enemyCalmEnemy()
{
	enemyStatus.currentFrameAnimation = amountStatesAnimationEnemy.calm;
	animation.setAnimations(enemy, enemyStatus.currentFrameAnimation);
}



void Enemy::enemyMove(float deltaTime)
{
	float position = physics.getPositon().x;
	if (position < enemyMoveStatus.startPoint.x + enemyMoveStatus.maximumDistanceBackward ||  position > enemyMoveStatus.startPoint.x + enemyMoveStatus.maximumDistanceForward)
	{	
		enemyMoveStatus.direction.x = -1 * enemyMoveStatus.direction.x;
	}
	physics.updatePhysics(enemyMoveStatus.direction, deltaTime);
	healthBar->setPosition(enemy.getPosition().x + enemyStatus.OFFSET_HEALTH_BAR_X, enemy.getPosition().y + enemyStatus.OFFSET_HEALTH_BAR_Y);


}

void Enemy::enemyFightAnimation(float& deltaTime)
{
	enemyStatus.timeElapsedToUpdateAnimation += deltaTime;
	if (enemyStatus.timeElapsedToUpdateAnimation > enemyStatus.timeToShiftAnimation)
	{
		enemyStatus.timeElapsedToUpdateAnimation = 0;
		enemyStatus.currentFrameAnimation++;
	}
	if (enemyStatus.currentFrameAnimation > amountStatesAnimationEnemy.live)
	{
		enemyStatus.currentFrameAnimation = 0;
		enemyShoot();
	}
	animation.setAnimations(enemy, enemyStatus.currentFrameAnimation);
}


void Enemy::enemyTakeShoots(std::vector<sf::Sprite>& bulletVector)
{
	if (checkIfHit(bulletVector))
	{
		enemyHited();
	}
}
bool Enemy::checkIfHit(std::vector<sf::Sprite>& bulletVector)
{
	for (unsigned int i = 0; i < bulletVector.size(); i++)
	{
		if (bulletVector[i].getPosition().y >= enemy.getPosition().y + 40 /*+ enemy.getGlobalBounds().height+ 20 */ &&
			(bulletVector[i].getPosition().x >= enemy.getPosition().x) && bulletVector[i].getPosition().x <= enemy.getPosition().x + enemy.getGlobalBounds().width)
		{
			std::cout << "hit ";
			bulletVector.erase(bulletVector.begin() + i);
			return true;
		}
	}
	return false;
}
void Enemy::enemyHited()
{
	delete healthBar;
	healthBar = new sf::RectangleShape;
	healthBar->setFillColor(sf::Color::Red);
	healthBar->setPosition(enemy.getPosition().x + enemyStatus.OFFSET_HEALTH_BAR_X, enemy.getPosition().y + enemyStatus.OFFSET_HEALTH_BAR_Y);
	if (enemyStatus.valueHealth != 0)
	{
		enemyStatus.valueHealth -= 20;
	}
	if (enemyStatus.valueHealth == 0)
	{
		healthState = HealthState::Dead;
		delete healthBar;
	}
	if (healthState == HealthState::Live)
	{
		healthBar->setSize(sf::Vector2f(enemyStatus.valueHealth, 10));
	}
}



void Enemy::enemyShoot()
{
	enemyBullet.setPosition(physics.getPositon().x - 30, physics.getPositon().y + 60);
	enemyBulletVector.push_back(enemyBullet);
}


void Enemy::Draw(sf::RenderTarget& window)
{
	for (int i = 0; i < enemyBulletVector.size(); i++)
	{
		window.draw(enemyBulletVector[i]);
	}
	window.draw(enemy);


	if (healthState == HealthState::Live)
	{
		window.draw(*healthBar);
	}
}

std::vector<sf::Sprite>* Enemy::enemyGetBullets()
{
	std::vector<sf::Sprite>* wsk = &enemyBulletVector;
	return wsk;
}

int Enemy::ifEnemyLive()
{
	if (healthState == HealthState::Dead)
		return 1;
	else
		return 0;

}






