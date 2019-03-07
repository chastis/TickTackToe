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
	while (temp_x !=0 && game._field[temp_x - 1][temp_y] == this->_my_cell)
	{
		points++;
		temp_x--;
	}
	if (points >= game._win_points) {
		game._playing = false; return true; }
	//horisontal
	temp_x = x;
	temp_y = y;
	points = 1;
	while (temp_y + 1 < game._size && game._field[temp_x][temp_y + 1] == this->_my_cell)
	{
		points++;
		temp_y++;
	}
	while (temp_y != 0 && game._field[temp_x][temp_y - 1] == this->_my_cell)
	{
		points++;
		temp_y--;
	}
	if (points >= game._win_points) {
		game._playing = false; return true; }
	//from bottom left to top right
	temp_x = x;
	temp_y = y;
	points = 1;
	while (temp_y + 1 < game._size && temp_x + 1 < game._size && game._field[temp_x + 1][temp_y + 1] == this->_my_cell)
	{
		points++;
		temp_y++;
		temp_x++;
	}
	while (temp_y != 0 && temp_x != 0 && game._field[temp_x - 1][temp_y - 1] == this->_my_cell)
	{
		points++;
		temp_y--;
		temp_x--;
	}
	if (points >= game._win_points) {
		game._playing = false; return true; }
	//fron bottom right to top left
	temp_x = x;
	temp_y = y;
	points = 1;
	while (temp_y + 1 < game._size && temp_x != 0 && game._field[temp_x - 1][temp_y + 1] == this->_my_cell)
	{
		points++;
		temp_y++;
		temp_x--;
	}
	while (temp_y != 0 && temp_x + 1 < game._size && game._field[temp_x + 1][temp_y - 1] == this->_my_cell)
	{
		points++;
		temp_y--;
		temp_x++;
	}
	if (points >= game._win_points) {
		game._playing = false; return true; }

	return false;
}
bool Player::make_turn(Game &game, sf::Vector2f pos)
{
	//check that we are on the field
	if (pos.x < 0 || pos.y < 0 || pos.x > 32 * game._size - 1 || pos.y > 32 * game._size - 1) return false;
	//transorm to matrix iterators
	size_t x = pos.x / 32, y = pos.y / 32;
	//check for empty cell
	if (game._field[x][y] != cell::empty) return false;
	//next pl turn
	game._first_p_turn = !game._first_p_turn;
	//put
	game._field[x][y] = this->_my_cell;
	//am i win?
	return am_i_win(game, x, y);
}