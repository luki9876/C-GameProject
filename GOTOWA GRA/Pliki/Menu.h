#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream> 
#include <iomanip>
#include <iostream>


#define NUMBER_OF_ITEMS_MAIN  3
#define NUMBER_OF_ITEMS_DEAD  3
#define NUMBER_OF_ITEMS_END  3

//#define NUMBER_OF_ITEMS_END  3

enum class Screens {Main, Dead, End};


struct offsetFirstWord 
{
	const int OFFSET_X = -425;
	const int OFFSET_Y = -167; // 160

};
struct offsetSecondWord
{
	const int OFFSET_X = -495;
	const int OFFSET_Y = -95; //90

};





class Menu
{
public:
	void createMenu(sf::Vector2u sizeWindow);
	void draw(sf::RenderTarget& window);
	void calculateResult(float score);
	bool ifEnableInitGame(float dt);
	void MoveUp();
	void MoveDown();
	int getDifficult();
	void setStateDead();
	void setStateEnd();


private:

	void initMainMenuElements();
	void initDeadElements();
	void initEndElements();

	float deltaTime;
	int selectedItemIndex;
	std::stringstream ss;
	sf::Vector2u dimensionWindow;
	Screens screens;
	
	int difficult;
	offsetFirstWord offsetFirstW;
	offsetSecondWord offsetSecondW;
	sf::Font font;
	
	sf::Text text[NUMBER_OF_ITEMS_MAIN];
	sf::Text deadText[NUMBER_OF_ITEMS_DEAD];
	sf::Text endText[NUMBER_OF_ITEMS_END];
	
	sf::Texture mainMenuTex;
	sf::Texture deadTex;
	sf::Texture endTex;

	sf::Sprite mainMenu;
	sf::Sprite dead;
	sf::Sprite end;






};

