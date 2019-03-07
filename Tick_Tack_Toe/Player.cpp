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
bool Player::am_i_win( Game &game, size_t x, size_t y)
{
	size_t temp_x = x, temp_y = y;
	size_t points = 1;
	//vertical
	while (temp_x + 1 < game._size && game._field[temp_x + 1][temp_y] == this->_my_cell)
	{
		points++;
		temp_x++;
	}
	while (temp_x - 1 >=0 && game._field[temp_x - 1][temp_y] == this->_my_cell)
	{
		points++;
		temp_x--;
	}
	if (points >= game._win_points) { game._playing = false; return true; }
	//horisontal
	points = 1;
	while (temp_y + 1 < game._size && game._field[temp_x][temp_y + 1] == this->_my_cell)
	{
		points++;
		temp_y++;
	}
	while (temp_y - 1 >= 0 && game._field[temp_x][temp_y - 1] == this->_my_cell)
	{
		points++;
		temp_y--;
	}
	if (points >= game._win_points) { game._playing = false; return true; }
	//from bottom left to top right
	points = 1;
	while (temp_y + 1 < game._size && temp_x + 1 < game._size && game._field[temp_x + 1][temp_y + 1] == this->_my_cell)
	{
		points++;
		temp_y++;
		temp_x++;
	}
	while (temp_y - 1 >= 0 && temp_x - 1 >= 0 && game._field[temp_x - 1][temp_y - 1] == this->_my_cell)
	{
		points++;
		temp_y--;
		temp_x--;
	}
	if (points >= game._win_points) { game._playing = false; return true; }
	//fron bottom right to top left
	points = 1;
	while (temp_y + 1 < game._size && temp_x - 1 >= 0 && game._field[temp_x - 1][temp_y + 1] == this->_my_cell)
	{
		points++;
		temp_y++;
		temp_x--;
	}
	while (temp_y - 1 >= 0 && temp_x + 1 < game._size && game._field[temp_x + 1][temp_y - 1] == this->_my_cell)
	{
		points++;
		temp_y--;
		temp_x++;
	}
	if (points >= game._win_points) { game._playing = false; return true; }

	return false;
}
bool Player::make_turn(Game &game)
{
	size_t x, y;
	std::cout << "Please give me the coordinats (x,y) of your next point" << std::endl;
	std::cin >> x >> y;

	//put
	game._field[x][y] = this->_my_cell;

	//am i win?
	return am_i_win(game, x, y);
}