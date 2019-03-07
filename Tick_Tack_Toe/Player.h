#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include <SFML\Graphics.hpp>

class Player
{
public:
	//friend class Game;

	Player();
	//are you a bot?
	//cell that you would to play
	Player(bool is_bot, cell my_cell);
	~Player();
	bool make_turn(Game &game, sf::Vector2f pos);
private:
	//check for win
	bool am_i_win(Game &game, size_t x, size_t y);
	//cell of this player
	cell _my_cell;
	//is this bot?
	bool _is_bot;
	
};
#endif // !PLAYER_H
