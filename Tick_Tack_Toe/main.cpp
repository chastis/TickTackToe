#include <iostream>
#include "Game.h"
#include "Player.h"

int main()
{
	Game game;
	Player p1(1, cell::x);
	Player p2(1, cell::o);


	game.print();
	while (game.playing())
	{
		p1.make_turn(game);
		game.print();
		p2.make_turn(game);
		game.print();
	}
	return 0;
}