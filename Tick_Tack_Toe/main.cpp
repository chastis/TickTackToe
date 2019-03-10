#include <iostream>
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Player.h"
#include "Menu.h"
#include "Message.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640), "Tick-Tack-Toe");

	Game game;
	Menu menu;
	Message msg;
	Player p1(0, cell::x);
	Player p2(0, cell::o);
	//who will make turn first?
	bool first_p_turn = true;
	//for only one time esc has been pressed
	bool esc_pressed = false;
	//loop
	while (window.isOpen())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window); //coord of mouse (in px)
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos); //coord of mous (transform)
		sf::Event event;
		
		//if we pressed esc we come to menu
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !esc_pressed)
		{
			esc_pressed = true;
			//esc in the menu return us at home
			if (menu.is_menu())
			{
				menu.reset();
			}
			//open menu;
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

		//maybe is AI turn now?
		if (game.playing() && !msg.is_message() && !menu.is_menu())
		{
			if (game.will_first_go() && p1.is_bot())
			{
				//std::cout << "AI's turn" << std::endl;
				if (p1.make_ai_turn(game)) msg.x_won = true;
			}
			else if (!game.will_first_go() && p2.is_bot())
			{
				//std::cout << "AI's turn" << std::endl;
				if (p2.make_ai_turn(game)) msg.o_won = true;
			}
		}

		while (window.pollEvent(event))
		{
	
			if (event.type == sf::Event::Closed)
				window.close();
			//message page
			if (msg.is_message())
				//pressed left mouse
				if (event.type == sf::Event::MouseButtonPressed)
					if (event.key.code == sf::Mouse::Left)
						if (msg.work(pos))
						{
							menu.open();
							break;
						}
			//menu page
			if (menu.is_menu())
			{
				//try to change color of menu's buttons
				menu.change_colors(pos);
				//pressed left mouse
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.key.code == sf::Mouse::Left)
					{
						menu.work(pos, window, game, p1, p2);
					}
				}

			} 
			//game coditions
			else if (game.playing())
			{
				if (event.type == sf::Event::MouseButtonPressed)
					if (event.key.code == sf::Mouse::Left)
					{
						if (game.will_first_go() && !p1.is_bot())
						{
							//std::cout << "Player 1's turn" << std::endl;
							if (p1.make_turn(game, pos)) msg.x_won = true;
						}
						else if (!p2.is_bot())
						{
							//std::cout << "Player 2's turn" << std::endl;
							if (p2.make_turn(game, pos)) msg.o_won = true;
						}
					}
				
			}
		}
		
		window.clear();
		if (menu.is_menu())
		{
			//if menu was opend we don't play anymore
			msg.x_won = false;
			msg.o_won = false;
			p1.reset();
			p2.reset();
			//draw
			menu.draw(window, game);

		}
		//if we are not in the menu we are playing
		else game.draw(window);
		if (!menu.is_menu())
		{
			//check for result messages
			//   win  o         win  x          nobody win
			if (msg.o_won || msg.x_won || !game.playing()) msg.draw_won(pos,window);
		}
		window.display();
	}
	return 0;
}