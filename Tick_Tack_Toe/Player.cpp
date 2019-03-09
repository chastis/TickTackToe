#include "Player.h"

//size of cell in px
#define CELL_SIZE 160

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
	//where recolor is variable that show us painting this line or not
	auto vertical_check = [&](bool recolor = false)
	{
		//start pos
		size_t temp_x = x, temp_y = y;
		size_t points = 1;
		//painting start pos if we have to
		if (recolor) game._field[temp_x][temp_y] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;

		//go right
		while (temp_x + 1 < game._size && game._field[temp_x + 1][temp_y] == this->_my_cell)
		{
			//painted
			if (recolor) game._field[temp_x + 1][temp_y] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
			points++;
			temp_x++;
		}
		//return start pos
		temp_x = x;
		temp_y = y;

		//go left
		while (temp_x != 0 && game._field[temp_x - 1][temp_y] == this->_my_cell)
		{
			//painted
			if (recolor) game._field[temp_x - 1][temp_y] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
			points++;
			temp_x--;
		}

		return points;
	};
	auto horizontal_check = [&](bool recolor = false)
	{
		size_t temp_x = x, temp_y = y;
		size_t points = 1;
		if (recolor) game._field[temp_x][temp_y] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
		while (temp_y + 1 < game._size && game._field[temp_x][temp_y + 1] == this->_my_cell)
		{
			if (recolor) game._field[temp_x][temp_y + 1] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
			points++;
			temp_y++;
		}
		temp_x = x;
		temp_y = y;
		while (temp_y != 0 && game._field[temp_x][temp_y - 1] == this->_my_cell)
		{
			if (recolor) game._field[temp_x][temp_y - 1] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
			points++;
			temp_y--;
		}
		return points;
	};
	auto from_bottom_left_to_top_right_check = [&](bool recolor = false)
	{
		size_t temp_x = x, temp_y = y;
		size_t points = 1;
		if (recolor) game._field[temp_x][temp_y] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
		while (temp_y + 1 < game._size && temp_x + 1 < game._size && game._field[temp_x + 1][temp_y + 1] == this->_my_cell)
		{
			if (recolor) game._field[temp_x + 1][temp_y + 1] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
			points++;
			temp_y++;
			temp_x++;
		}
		temp_x = x;
		temp_y = y;
		while (temp_y != 0 && temp_x != 0 && game._field[temp_x - 1][temp_y - 1] == this->_my_cell)
		{
			if (recolor) game._field[temp_x - 1][temp_y - 1] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
			points++;
			temp_y--;
			temp_x--;
		}
		return points;
	};
	auto from_bottom_right_to_top_left_check = [&](bool recolor = false)
	{
		size_t temp_x = x, temp_y = y;
		size_t points = 1;
		if (recolor) game._field[temp_x][temp_y] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
		while (temp_y + 1 < game._size && temp_x != 0 && game._field[temp_x - 1][temp_y + 1] == this->_my_cell)
		{
			if (recolor) game._field[temp_x - 1][temp_y + 1] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
			points++;
			temp_y++;
			temp_x--;
		}
		temp_x = x;
		temp_y = y;
		while (temp_y != 0 && temp_x + 1 < game._size && game._field[temp_x + 1][temp_y - 1] == this->_my_cell)
		{
			if (recolor) game._field[temp_x + 1][temp_y - 1] = (this->_my_cell == cell::o) ? cell::win_o : cell::win_x;
			points++;
			temp_y--;
			temp_x++;
		}
		return points;
	};
	//vertical
	if (vertical_check() >= game._win_points)
	{
		vertical_check(true);
		game._playing = false;
		return true;
	}
	//horisontal
	if (horizontal_check() >= game._win_points)
	{
		horizontal_check(true);
		game._playing = false;
		return true;
	}
	//from bottom left to top right
	if (from_bottom_left_to_top_right_check() >= game._win_points)
	{
		from_bottom_left_to_top_right_check(true);
		game._playing = false;
		return true;
	}
	//fron bottom right to top left
	if (from_bottom_right_to_top_left_check() >= game._win_points)
	{
		from_bottom_right_to_top_left_check(true);
		game._playing = false;
		return true;
	}

	return false;
}

bool Player::make_turn(Game &game, sf::Vector2f pos)
{
	//check that we are on the field
	if (pos.x < 0 || pos.y < 0 || pos.x > CELL_SIZE * game.x_scale * game._size - 1 || pos.y > CELL_SIZE * game.y_scale * game._size - 1) return false;
	//transorm to matrix iterators
	size_t x = pos.x / (CELL_SIZE * game.x_scale), y = pos.y / (CELL_SIZE * game.y_scale);
	//check for empty cell
	if (game._field[x][y] != cell::empty) return false;
	//next player turn
	game._first_p_turn = !game._first_p_turn;
	//one turn less
	game._turns--;
	//put
	game._field[x][y] = this->_my_cell;
	//am i win?
	return am_i_win(game, x, y);
}