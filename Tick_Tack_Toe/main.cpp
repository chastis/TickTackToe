#include <iostream>
#include "Game.h"
#include "Player.h"
#include <conio.h>

int main()
{
	Game game;
	Player p1(1, cell::x);
	Player p2(1, cell::o);


	game.print();
	while (game.playing())
	{
		if (p1.make_turn(game))
		{
			game.print();
			std::cout << "WOW PLAYER 1 WIN!!!" << std::endl;
		}
		else if (p2.make_turn(game))
		{
			game.print();
			std::cout << "WOW PLAYER 2 WIN!!!" << std::endl;
		} else game.print();
	}

	_getch();
	return 0;
}