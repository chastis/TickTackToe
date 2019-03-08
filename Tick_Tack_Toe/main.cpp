#include <iostream>
#include <conio.h>
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Player.h"
#include "Menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "Tick-Tack-Toe");

	Game game;
	Menu menu;
	Player p1(1, cell::x);
	Player p2(1, cell::o);
	bool first_p_turn = true;
	bool esc_pressed = false;


	while (window.isOpen())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //coord of mouse (in px)
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos); //coord of mous (transform)
		sf::Event event;
				
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !esc_pressed)
		{
			esc_pressed = true;
			if (menu.is_menu())
			{
				menu.reset();
				//i will think about this
				//menu.close();
			}
			else
			{
				menu.reset();
				menu.open();
			}
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && esc_pressed)
		{
			esc_pressed = false;
		}

		
		while (window.pollEvent(event))
		{
	
			if (event.type == sf::Event::Closed)
				window.close();

			if (menu.is_menu())
			{
				menu.change_colors(pos);
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.key.code == sf::Mouse::Left)
					{
						menu.work(pos, window, game);
					}
				}

			} 
			else if (game.playing())
			{
				if (event.type == sf::Event::MouseButtonPressed)
					if (event.key.code == sf::Mouse::Left)
					{
						if (game.will_first_go())
						{
							if (p1.make_turn(game, pos)) std::cout << "Player 1 have won!" << std::endl;
						}
						else
						{
							if (p2.make_turn(game, pos)) std::cout << "Player 2 have won!" << std::endl;
						}
						game.print();
					}
				
			}
		}
		
		window.clear();
		if (menu.is_menu()) menu.draw(window,game); else game.draw(window);
		window.display();
	}
	//_getch();
	return 0;
}