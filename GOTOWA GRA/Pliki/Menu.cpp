#include "Menu.h"



void Menu::createMenu(sf::Vector2u sizeWindow)
{
	screens = Screens::Main;
	dimensionWindow = sizeWindow;
	difficult = 1;
	selectedItemIndex = 0;
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Nie udalo sie zaladowac czcionki";
	}

	initMainMenuElements();
	initDeadElements();
	initEndElements();
	deltaTime = 0;

}



void Menu::calculateResult(float score)
{

	ss << std::fixed << std::setprecision(2)  << score;
	deadText[1].setString(ss.str());
	endText[1].setString(ss.str());
}


bool Menu::ifEnableInitGame(float dt)
{
	deltaTime += dt;
	if (deltaTime >= 0.15)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			MoveUp();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			MoveDown();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selectedItemIndex == 0)
		{
			screens = Screens::End;
			return true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selectedItemIndex == 1)
		{
			if (difficult < 4)
			{
				difficult++;
			}
			else
			{
				difficult = 1;
			}

			if (difficult == 1)
			{
				text[2].setString("Easy");
			}
			else if (difficult == 2)
			{
				text[2].setString("Medium");
			}
			else
			{
				text[2].setString("Hard");
			}

			deltaTime = 0;
		}
	}
	return false;
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		text[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		text[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < 2)
	{
		text[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		text[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::getDifficult()
{
	return 6 - difficult;
}

void Menu::setStateDead()
{
	screens = Screens::Dead;
}

void Menu::setStateEnd()
{
	screens = Screens::End;
}


void Menu::initMainMenuElements()
{

	if (!mainMenuTex.loadFromFile("texture/mainM.png"))
	{
		std::cout << "Nie udalo sie zaladowac textury menu";
	}
	mainMenu.setTexture(mainMenuTex);
	text[0].setFont(font);
	text[0].setString("Play");
	text[0].setFillColor(sf::Color::Red);
	text[0].setPosition(sf::Vector2f(dimensionWindow.x + offsetFirstW.OFFSET_X, dimensionWindow.y + offsetFirstW.OFFSET_Y));

	text[1].setFont(font);
	text[1].setString("Difficult: ");
	text[1].setPosition(sf::Vector2f(dimensionWindow.x + offsetSecondW.OFFSET_X, dimensionWindow.y + offsetSecondW.OFFSET_Y));

	text[2].setFont(font);
	text[2].setString("Easy");
	text[2].setPosition(sf::Vector2f(dimensionWindow.x + offsetSecondW.OFFSET_X + 115, dimensionWindow.y + offsetSecondW.OFFSET_Y));

}

void Menu::initDeadElements()
{
	if (!deadTex.loadFromFile("texture/DeadScreen.png"))
	{
		std::cout << "Nie udalo sie zaladowac textury ekranu porazki";
	}
	dead.setTexture(deadTex);

	deadText[0].setFont(font);
	deadText[0].setString("Twoj wynik: ");
	deadText[0].setPosition(260, 222);

	deadText[1].setFont(font);
	deadText[1].setPosition(430, 222);
}

void Menu::initEndElements()
{
	if (!endTex.loadFromFile("texture/Wygrana.png"))
	{
		std::cout << "Nie udalo sie zaladowac textury ekranu wygrana";
	}
	end.setTexture(endTex);

	endText[0].setFont(font);
	endText[0].setString("Twoj wynik: ");
	endText[0].setPosition(270, 215);

	endText[1].setFont(font);
	endText[1].setPosition(430, 215);

}


void Menu::draw(sf::RenderTarget& window)
{
	if (screens == Screens::Main)
	{
		window.draw(mainMenu);
		for (int i = 0; i < NUMBER_OF_ITEMS_MAIN; i++)
		{
			window.draw(text[i]);
		}
	}
	else if (screens == Screens::Dead)
	{
		window.draw(dead);
		for (int i = 0; i < NUMBER_OF_ITEMS_DEAD; i++)
		{
			window.draw(deadText[i]);
		}
	}
	else if (screens == Screens::End)
	{
		window.draw(end);
		for (int i = 0; i < NUMBER_OF_ITEMS_END; i++)
		{
			window.draw(endText[i]);
		}
	}


}