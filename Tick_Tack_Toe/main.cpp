#include <iostream>
#include <conio.h>
#include <SFML\Graphics.hpp>
#include "Game.h"
#include "Player.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Tick-Tack-Toe");

	Game game;
	Player p1(1, cell::x);
	Player p2(1, cell::o);
	bool first_p_turn = true;

	while (window.isOpen())
	{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//coord of mouse (in px)
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);//coord of mous (transform)


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (game.playing())
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
		game.draw(window);
		window.display();
	}
	_getch();
	return 0;
}