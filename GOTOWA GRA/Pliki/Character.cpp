#include "Character.h"
#include <iostream>

//using namespace sf;


Character::Character()
{
	setDirection(Direction::None);
	positionInFileDifferentAnimation.WalkingAndShooting = sf::Vector2f(playerStates.WIDTH_TEXTURE_CHARACTER, 2 * playerStates.HEIGHT_TEXTURE_CHARACTER);
	positionInFileDifferentAnimation.Walking = sf::Vector2f(playerStates.WIDTH_TEXTURE_CHARACTER, playerStates.HEIGHT_TEXTURE_CHARACTER);
	positionInFileDifferentAnimation.Shooting = sf::Vector2f(playerStates.WIDTH_TEXTURE_CHARACTER, 0);
	positionInFileDifferentAnimation.Idle = sf::Vector2f(playerStates.WIDTH_TEXTURE_CHARACTER, 0);
	positionInFileDifferentAnimation.Dead = sf::Vector2f(playerStates.WIDTH_TEXTURE_CHARACTER, 3 * playerStates.HEIGHT_TEXTURE_CHARACTER);

	playerStates.currentFrameAnimation = 0;
	playerStates.timeToShiftAnimation = 1.0f/10;
	playerStates.sumTime = 0;
	playerStates.shoot = false;
	playerStates.jump = false;

	if (!BulletTex.loadFromFile("texture/bullet_rifle.png"))
	{
		std::cout << "Nie udalo sie zaladowac tekstury pocisku pistoletu";
	}
	Bullet.setTexture(BulletTex);
	Bullet.setScale(0.03, 0.03);
	bulletStates.timeElapsedToGenerateNewBullets = 0;

	if (!heartTex.loadFromFile("texture/heart.png"))
	{
		std::cout << "Nie udalo sie zaladowac tekstury zycia";
	}
	heart.setTexture(heartTex);

	points.score= 0;
	points.maximumDistance = 0;

}

void Character::InitCharacter(std::string TexLocation, const int* tab, 
	int l_widthTab, int l_heightTab, sf::Vector2f startPosition, sf::Vector2f l_speed)
{
	animation.setTexture(Sprite, TexLocation);			
	animation.setSizeRenderWindow(sf::Vector2f(playerStates.WIDTH_TEXTURE_CHARACTER, playerStates.HEIGHT_TEXTURE_CHARACTER));
	idle();
	physics.InitPhysics(&Sprite, tab, l_widthTab, l_heightTab, 1, sf::Vector2f(-27, -11), sf::Vector2f (l_speed) );
	physics.setPosition(sf::Vector2f(startPosition));
	Bullet.setPosition(Sprite.getPosition().x + 20, Sprite.getPosition().y+ 45);
	tile.amountTileX = l_widthTab;


	for (int i = 0; i < health.amountLives; i++)
	{
		health.heartVector.push_back(heart);
	}

}
void Character::detectActions()
{
	setDirection(Direction::None);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { playerStates.jump = true; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { setDirection(Direction::Right); }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { setDirection(Direction::Left); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { playerStates.shoot = true; generateBullets(); }
}

void Character::setDirection(Direction l_dir) 
{ 
	m_dir = l_dir; 
}

void Character::handleActions()
{
	if (m_dir != Direction::None || playerStates.shoot)
	{
		if (m_dir != Direction::None && playerStates.shoot)	// animation walking and shooting
		{
			walkingAndShooting();
		}
		else if (m_dir != Direction::None)			//animation walking
		{
			walking();
		}
		else							//animation shoot
		{
			shooting();
		}

		if (m_dir == Direction::Left)
		{
			playerStates.direction.x = -1;
		}
		else if (m_dir == Direction::Right)
		{
			playerStates.direction.x = 1;
		}
		else
		{
			playerStates.direction = sf::Vector2f(0, 0);
		}

		playerStates.shoot = false;
	}
	else
	{
		playerStates.direction = sf::Vector2f(0, 0);
		idle();
	}

}

void Character::walkingAndShooting()
{
	animation.setPositionTecture(positionInFileDifferentAnimation.WalkingAndShooting);
	animation.updateRenderWindow(amountStatesAnimation.WALKING_AND_SHOOTING);
	playerStates.maximumFrameAnimation = amountStatesAnimation.WALKING_AND_SHOOTING;
}

void Character::walking()
{
	animation.setPositionTecture(positionInFileDifferentAnimation.Walking);
	animation.updateRenderWindow(amountStatesAnimation.WALKING);
	playerStates.maximumFrameAnimation = amountStatesAnimation.WALKING;
}

void Character::shooting()
{
	animation.setPositionTecture(positionInFileDifferentAnimation.Shooting);
	animation.updateRenderWindow(amountStatesAnimation.SHOOTING);
	playerStates.maximumFrameAnimation = amountStatesAnimation.SHOOTING;
}

void Character::idle()
{
	animation.setPositionTecture(positionInFileDifferentAnimation.Idle);
	animation.updateRenderWindow(amountStatesAnimation.IDLE);
	playerStates.maximumFrameAnimation = amountStatesAnimation.IDLE;
}

void Character::dead()
{
	animation.setPositionTecture(positionInFileDifferentAnimation.Dead);
	animation.updateRenderWindow(amountStatesAnimation.DEAD);
	playerStates.maximumFrameAnimation = amountStatesAnimation.DEAD;
}


void Character::handleInput(void)
{
	detectActions();
	handleActions();

}


void Character::Update(float& deltaTime, std::vector<sf::Sprite>& enemyBulletVector, float positionViewX)
{
	checkIfHit(enemyBulletVector);
	if (playerHealthState == PlayerHealthState::Live)
	{
		if (ifUnderMap())
		{
			health.amountLives--;
			if (health.amountLives == 0)
			{
				playerHealthState = PlayerHealthState::Dead;
			}
		}

		handleInput();
		if (playerStates.jump == true)
		{
			physics.jump(playerStates.JUMP_FORCE);
			playerStates.jump = false;
		}
		updateBullets(deltaTime);
		physics.updatePhysics(sf::Vector2f(playerStates.direction), deltaTime);
		updateHeart(positionViewX);
		ifCompleteLevel();
		updateDistansPoints();
	}
	else
	{
		//	dead();
	}

	UpdateAnimation(deltaTime);
	setAnimation();
}

void Character::UpdateAnimation(float dTime)
{
	playerStates.sumTime += dTime;
	if (playerStates.sumTime > playerStates.timeToShiftAnimation)
	{
		playerStates.currentFrameAnimation++;
		playerStates.sumTime = 0;
	}
	if (playerStates.currentFrameAnimation >= playerStates.maximumFrameAnimation)
	{
		playerStates.currentFrameAnimation = 0;
	}
}

void Character::updateHeart(float positionView)
{

	for (int i = 0; i < health.amountLives; i++)
	{
		health.heartVector[i].setPosition(positionView - health.POSITION.x + i * 32, health.POSITION.y);
	}

}

bool Character::ifUnderMap()
{
	if (getPosition().y > 600)
	{
		sf::Vector2f pos = getPosition();
		pos.x -= playerStates.RESPAWN_X_VALUE;
		pos.y -= playerStates.RESPAWN_Y_VALUE;
		physics.setPosition(pos);
		return true;
	}
	return false;
}

void Character::setAnimation(void)
{
	animation.setAnimations(Sprite, playerStates.currentFrameAnimation);
}


void Character::ifCompleteLevel()
{
	if (getPosition().x > (tile.amountTileX - 3)* tile.SIZE_TILE_X)
	{
		playerHealthState = PlayerHealthState::CompleteLevel;
	}
}

void Character::generateBullets()
{
	bulletStates.timeElapsedToGenerateNewBullets += dTime;
	if (bulletStates.timeElapsedToGenerateNewBullets > bulletStates.TIME_TO_MAKE_NEW_BULLETS)
	{
		Bullet.setPosition(Sprite.getPosition().x + bulletStates.CORRECT_POSITION_BULLET_X, Sprite.getPosition().y + bulletStates.CORRECT_POSITION_BULLET_Y);
		bulletsVector.push_back(Bullet);
		bulletStates.timeElapsedToGenerateNewBullets = 0;
	}

}

void Character::updateBullets(float dt)
{
	dTime = dt;
	for (unsigned i = 0; i < bulletsVector.size(); i++)
	{
		bulletsVector[i].move(bulletStates.SPEED_BULLET* dt, 0);
		if (bulletsVector[i].getPosition().x > bulletStates.RANGE + getPosition().x)
		{
			bulletsVector.erase(bulletsVector.begin() + i);
		}
	}
	
}

void Character::updateDistansPoints()
{
	if (getPosition().x > points.maximumDistance)
	{
		points.maximumDistance = getPosition().x;
		points.score += points.POINTS_FOR_DISTANCE;
	}

}

void Character::checkIfHit(std::vector<sf::Sprite>& enemyBulletVector)
{
	for (int i = 0; i < enemyBulletVector.size(); i++)
	{
		//std::cout << "player Y: " << getPosition().y << " " << "bullet pos Y: " << enemyBulletVector[i].getPosition().y << "\n";
		if (enemyBulletVector[i].getPosition().x + bulletStates.OFFSET_HIT_PLAYER_X < getPosition().x
			&& enemyBulletVector[i].getPosition().x > getPosition().x 
			&& enemyBulletVector[i].getPosition().y - 5 > getPosition().y
			&& enemyBulletVector[i].getPosition().y < getPosition().y + bulletStates.OFFSET_HIT_PLAYER_Y)
		{
			enemyBulletVector.erase(enemyBulletVector.begin() + i);
	//		health.heartVector.erase(health.heartVector.begin() + health.amountLives);
			health.amountLives--;
			if (health.amountLives == 0)
			{
				playerHealthState = PlayerHealthState::Dead;
			}

		}
	}

}

bool Character::isLife()
{
	if (playerHealthState == PlayerHealthState::Live)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int Character::getScore()
{
	return points.score;
}

int Character::getTypeEndGame()
{
	if (playerHealthState == PlayerHealthState::Dead)
		return 1;
	else if (playerHealthState == PlayerHealthState::CompleteLevel)
		return 2;
}

void Character::setAmountLives(int lives)
{
	health.amountLives = lives;
}



sf::Vector2f Character::getPosition()
{
	return sf::Vector2f(Sprite.getPosition());
}


void Character::Draw(sf::RenderTarget &window)
{
	//rectangle.setPosition(m_bottomRight);
	window.draw(Sprite);
	for (unsigned i = 0; i < bulletsVector.size(); i++)
		window.draw(bulletsVector[i]);
	for (int i = 0; i < health.amountLives; i++)
	{
		window.draw(health.heartVector[i]);
	}

}

std::vector<sf::Sprite> *Character::getBullets()
{
	std::vector<sf::Sprite> *wsk = &bulletsVector;

	return wsk;
}

