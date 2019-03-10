#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include <SFML\Graphics.hpp>
#include <vector>

class Player
{
public:
	friend class Menu;
	Player();
	//are you a bot?
	//cell that you would to play
	Player(bool is_bot, cell my_cell);
	~Player();
	//turn of player
	bool make_turn(Game &game, sf::Vector2f pos);
	//ai turn
	bool make_ai_turn(Game &game);
	//are you a bot?
	bool is_bot();
	//reset to start;
	//void reset();

private:
	//check for win
	bool am_i_win(Game &game, size_t x, size_t y);
	//cell of this player
	cell _my_cell;
	//is this bot?
	bool _is_bot;
	
};

std::vector<Attack>& give_attack(Game& game, cell my_cell);

void upgrade_attack(Game& game, cell _my_cell, int x, int y);

#endif // !PLAYER_H
