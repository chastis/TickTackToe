#include "Player.h"
#include <iostream>
#include <set>

//size of cell in px
#define CELL_SIZE 160

std::vector<Attack>& give_attack(Game& game, cell my_cell)
{
	if (cell::x == my_cell) return game._p1_attacks;
	else return game._p2_attacks;
}

void upgrade_attack(Game& game, cell _my_cell, int x, int y)
{
	Attack temp_attack(game, x, y, x, y,_my_cell);
	Point temp_point(x, y), touch_point(-1, -1);
	std::set<Point> used_points;
	give_attack(game, _my_cell).push_back(temp_attack);
	size_t size = give_attack(game, _my_cell).size();
	for (int i = 0; i < size - 1; i++)
	{
		if (give_attack(game, _my_cell)[i].line.touch(temp_point, touch_point) && used_points.find(touch_point) == used_points.end())
		{
			used_points.insert(touch_point);
			if (give_attack(game, _my_cell)[i].line.len == 1)
			{
				give_attack(game, _my_cell).push_back(give_attack(game, _my_cell)[i]);
				give_attack(game, _my_cell)[give_attack(game, _my_cell).size() - 1].space = -42;
			}
			give_attack(game, _my_cell)[i].line.add_point(temp_point);
		}

	}
	if (used_points.size() >= 2)
	{
		merge(give_attack(game, _my_cell));
	}
	for (int i = 0; i < give_attack(game, _my_cell).size(); i++)
	{
		give_attack(game, _my_cell)[i].update(game, _my_cell);
		if (give_attack(game, _my_cell)[i].potential == 0)
		{
			//give_attack(game, _my_cell).erase(give_attack(game, _my_cell).begin() + i);
			//i--;
			continue;
		}
	}
}

void upgrade_attack(std::vector<Attack>& attacks, Game& game, cell _my_cell, int x, int y)
{
	Attack temp_attack(game, x, y, x, y, _my_cell);
	Point temp_point(x, y), touch_point(-1, -1);
	std::set<Point> used_points;
	attacks.push_back(temp_attack);
	size_t size = attacks.size();
	for (int i = 0; i < size - 1; i++)
	{
		if (attacks[i].line.touch(temp_point, touch_point) && used_points.find(touch_point) == used_points.end())
		{
			used_points.insert(touch_point);
			if (attacks[i].line.len == 1)
			{
				attacks.push_back(attacks[i]);
				attacks[attacks.size() - 1].space = -42;
			}
			attacks[i].line.add_point(temp_point);
		}

	}
	if (used_points.size() >= 2)
	{
		merge(attacks);
	}
	for (int i = 0; i < give_attack(game, _my_cell).size(); i++)
	{
		attacks[i].update(game, _my_cell);
		if (attacks[i].potential == 0)
		{
			//attacks.erase(attacks.begin() + i);
			//i--;
			continue;
		}
	}
}

void set(std::vector<Attack>& here, std::vector<Attack>& from)
{
	here.clear();
	for (auto now : from)
	{
		here.push_back(now);
	}
}
Player::Player()
{
	_is_bot = 1;
	_my_cell = cell::x;
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
	//put this point like the latest
	game._last_x = x;
	game._last_y = y;
	/////////////////////////////////////////////////////////////////////
	upgrade_attack(game, _my_cell, x, y);
	/////////////////////////////////////////////////////////////////////
	//am i win?
	return am_i_win(game, x, y);
}

bool Player::is_bot()
{
	return _is_bot;
}

bool Player::make_ai_turn(Game &game)
{;
	//give next turn to opponent
	game._first_p_turn = !game._first_p_turn;
	//one turn less
	game._turns--;
	size_t x = game._size / 2, y = game._size / 2;
	

	//for the first of all try to make turn in the center
	if (game._field[x][y] == cell::empty)
	{
		//everything is OK
	}
	else if (game._field[x][y] != _my_cell && game._field[x - 1][y - 1] == cell::empty)
	{
		x--;
		y--;
	}
	else
	{
		bool we_win = false;
		//AI itself
		int max_w = 0;
		for (int i = 0; i < game._size && !we_win; i++)
			for (int j = 0; j < game._size && !we_win; j++)
				if (game._field[i][j] == cell::empty)
				{
					cell not_my_cell = _my_cell == cell::x ? cell::o : cell::x;
					int temp_w_1 = 0;
					int temp_w_2 = 0;
					
					if (amount_nearby_cell(game, i, j, not_my_cell) != 0)
					{
						std::vector<Attack> temp_2;
						set(temp_2, give_attack(game, not_my_cell));
						upgrade_attack(temp_2, game, not_my_cell, i, j);
						temp_w_1 += count_weight(temp_2, i, j, game._win_points) - 1;
						//todo
					}
					//if (amount_nearby_cell(game, i, j, _my_cell) != 0)
					{
						std::vector<Attack> temp;
						set(temp, give_attack(game, _my_cell));
						upgrade_attack(temp, game, _my_cell, i, j);
						temp_w_2 += count_weight(temp, i, j, game._win_points);
						//todo
					}
					if (temp_w_2 == 99999)
					{
						we_win = true;
					}
					if (temp_w_2 >= 5000 && temp_w_1 != 99999)
					{
						temp_w_2 *= 2;
					}
					//attack mod
					//if (_my_cell == cell::x) temp_w_2 += temp_w_2 / 2;
					if (temp_w_1 + temp_w_2 > max_w)
					{
						max_w = temp_w_1 + temp_w_2;
						x = i;
						y = j;
					}

				}
				//else we cannot put cell in there
		std::cout << "THE MOST THE MOST MAX WEIGHT: " << max_w << std::endl;
	}


	//time delay
	sf::Clock clock;
	sf::Time elapsed = clock.getElapsedTime();
	sf::Time end_time = sf::seconds(1);
	while (elapsed < end_time)
	{
		elapsed = clock.getElapsedTime();
	}
	//put!
	game._field[x][y] = _my_cell;
	//add this point like a attack
	upgrade_attack(game, _my_cell, x, y);
	//put this point like the latest
	game._last_x = x;
	game._last_y = y;
	//check win
	return am_i_win(game, x, y);
}