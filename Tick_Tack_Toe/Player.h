#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"

class Player
{
public:
	friend class Game;

	Player();
	//are you a bot?
	//cell that you would to play
	Player(bool is_bot, cell my_cell);
	~Player();
	void make_turn(Game &game);
private:
	//cell of this player
	cell _my_cell;
	//is this bot?
	bool _is_bot;
};
#endif // !PLAYER_H
