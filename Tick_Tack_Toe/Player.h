#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include "Line.h"
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
	void reset();

private:
	//check for win
	bool am_i_win(Game &game, size_t x, size_t y);
	//cell of this player
	cell _my_cell;
	//is this bot?
	bool _is_bot;
	//enemys line
	std::vector<Line> defends;
	//my line
	std::vector<Line> attacks;
	
};

#endif // !PLAYER_H
