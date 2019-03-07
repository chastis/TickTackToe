#include "Player.h"
#include <iostream>

Player::Player()
{

}

Player::Player(bool is_bot, cell my_cell)
{
	_is_bot = is_bot;
	_my_cell = my_cell;
}

Player::~Player()
{

}

void Player::make_turn(Game &game)
{
	size_t x, y;
	std::cout << "Please give me the coordinats (x,y) of your next point" << std::endl;
	std::cin >> x >> y;

	game._field[x][y] = this->_my_cell;
}