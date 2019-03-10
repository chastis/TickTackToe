#include "Player.h"
#include <iostream>
#include <set>

//size of cell in px
#define CELL_SIZE 160

const bool operator <(const Point &a, const Point &b)
{
	if (a.x < b.x) return true;
	else if (a.x > b.x) return false;
	else return (a.y < b.y);

}

const bool operator ==(const Point &a, const Point &b)
{
	if (a.x == b.x && a.y == b.y) return true; else return false;
}

void merge(std::vector<Line> &lines)
{

	for (int i = 0; i < lines.size(); i++)
	{
		for (int j =  i + 1; j < lines.size(); j++)
		{
			if (lines[i].end == lines[j].start && lines[i].type == lines[j].type)
			{
				lines[i].end = lines[j].end;
				lines[i].len += lines[j].len - 1;
				lines.erase(lines.begin() + j);
				i--;
				break;
			}
			if (lines[i].start == lines[j].end && lines[i].type == lines[j].type)
			{
				lines[i].start = lines[j].start;
				lines[i].len += lines[j].len - 1;
				lines.erase(lines.begin() + j);
				i--;
				break;
			}
		}

	}
}

Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

Line::Line()
{
	start;
	end;
	len = 0;
	type = lines_type::point;
}

Line::Line(int x1, int y1, int x2, int y2)
{
	if (x1 < x2)
	{
		start.x = x1;
		start.y = y1;
		end.x = x2;
		end.y = y2;
	}
	else if (x2 < x1)
	{
		start.x = x2;
		start.y = y2;
		end.x = x1;
		end.y = y1;
	}
	else if (y1 < y2)
	{
		start.x = x1;
		start.y = y1;
		end.x = x2;
		end.y = y2;
	}
	else
	{
		start.x = x2;
		start.y = y2;
		end.x = x1;
		end.y = y1;
	}
	
	len = std::abs(x2 - x1) > std::abs(y2 - y1) ? std::abs(x2 - x1) + 1 : std::abs(y2 - y1) + 1;
	if (len == 1)
	{
		type = lines_type::point;
	}
	else
	{
		if (start.x == end.x) type = lines_type::vertical;
		else if (start.y == end.y) type = lines_type::horizontal;
		else if (start.y > end.y) type = lines_type::bot_left_top_right;
		else type = lines_type::bot_right_top_left;
	}
}

void Line::print()
{
	std::cout << "(" << start.x << " " << start.y << ") (" << end.x << " " << end.y << ")" << std::endl;
}

void Line::add_point(Point p)
{
	{
		//horiontal line
		if (start.y == end.y)
		{
			if (start.x != 0 && start.y == p.y && p.x == start.x - 1)
			{
				start.x--;
				len++;
				type = lines_type::horizontal;
				return;
			}
			if (end.y == p.y && p.x == end.x + 1)
			{
				end.x++;
				len++;
				type = lines_type::horizontal;
				return;
			}
		}
		//vertical
		if (start.x == end.x)
		{
			if (start.y != 0 && start.x == p.x && p.y == start.y - 1)
			{
				start.y--;
				len++;
				type = lines_type::vertical;
				return;
			}
			if (end.x == p.x && p.y == end.y + 1)
			{
				end.y++;
				len++;
				type = lines_type::vertical;
				return;
			}
		}
		//diagonal
		//from bottom left to top right
		if (len == 1 || start.x < end.x && start.y > end.y)
		{
			if (start.x - 1 == p.x && p.y == start.y + 1)
			{
				start.x--;
				start.y++;
				len++;
				type = lines_type::bot_left_top_right;
				return;
			}
			if (end.y != 0 && end.x + 1 == p.x && p.y == end.y - 1)
			{
				end.x++;
				end.y--;
				len++;
				type = lines_type::bot_left_top_right;
				return;
			}
		}
		//from bottom right to top left
		if (len == 1 || start.x < end.x && start.y < end.y)
		{
			if (start.y != 0 && start.x != 0 && start.x - 1 == p.x && p.y == start.y - 1)
			{
				start.x--;
				start.y--;
				len++;
				type = lines_type::bot_right_top_left;
				return;
			}
			if (end.x + 1 == p.x && p.y == end.y + 1)
			{
				end.x++;
				end.y++;
				len++;
				type = lines_type::bot_right_top_left;
				return;
			}
		}
	}
}

bool Line::touch(Point p, Point &touch_point)
{
	//horizontal line
	if (start.y == end.y)
	{
		if (start.x != 0 && start.y == p.y && p.x == start.x - 1)
		{
			touch_point = start;
			return true;
		}
		else if (end.y == p.y && p.x == end.x + 1)
		{
			touch_point = end;
			return true;
		}
	}
	//vertical
	if (start.x == end.x)
	{
		if (start.y != 0 && start.x == p.x && p.y == start.y - 1)
		{
			touch_point = start;
			return true;
		}
		else if (end.x == p.x && p.y == end.y + 1)
		{
			touch_point = end;
			return true;
		}
	}
	//diagonal
	//from bottom left to top right
	if (len == 1 || start.x < end.x && start.y > end.y)
	{
		if (start.x - 1 == p.x && p.y == start.y + 1)
		{
			touch_point = start;
			return true;
		}
		else if (end.y != 0 && end.x + 1 == p.x && p.y == end.y - 1)
		{
			touch_point = end;
			return true;
		}
	}
	//from bottom right to top left
	if (len == 1 || start.x < end.x && start.y < end.y)
	{
		if (start.y != 0 && start.x != 0 && start.x - 1 == p.x && p.y == start.y - 1)
		{
			touch_point = start;
			return true;
		}
		else if (end.x + 1 == p.x && p.y == end.y + 1)
		{
			touch_point = end;
			return true;
		}
	}
	return false;
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
	Line temp_line(x, y, x, y);
	Point temp_point(x, y), touch_point(-1,-1);
	std::set<Point> used_points;
	attacks.push_back(temp_line);
	size_t size = attacks.size();
	for (int i = 0; i < size - 1; i++)
	{
		if (attacks[i].touch(temp_point,touch_point) && used_points.find(touch_point) == used_points.end())
		{
			used_points.insert(touch_point);
			std::cout << "touch_point = (" << touch_point.x << " " << touch_point.y << ")" << std::endl;
			//error
			std::cout << "i=" << i << std::endl;
			if (attacks[i].len == 1)
			{
				attacks.push_back(attacks[i]);
			}
			//enderror
			attacks[i].add_point(temp_point);
		}
	}

	if (used_points.size() >= 2)
	{
		std::cout << "attack before merge" << std::endl;
		for (int i = 0; i < attacks.size(); i++)
		{
			attacks[i].print();
		}
		merge(attacks);
	}
	std::cout << "attack!" << std::endl;
	for (int i = 0; i < attacks.size(); i++)
	{
		attacks[i].print();
	}
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
		game._field[x][y] = _my_cell;
		//add this point like a attack
		Line temp(x, y, x, y);
	}
	else if (game._size == 2)
	{
		x = y = 0;
		while (game._field[x][y] != cell::empty)
		{
			if (x == 0) x++; else
			{
				y++;
				x--;
			}
		}
		game._field[x][y] = _my_cell;
	}
	else
	{
		//AI itself
		

	}



	//time delay
	sf::Clock clock;
	sf::Time elapsed = clock.getElapsedTime();
	sf::Time end_time = sf::seconds(2);
	while (elapsed < end_time)
	{
		elapsed = clock.getElapsedTime();
	}
	//put this point like the latest
	game._last_x = x;
	game._last_y = y;
	//check win
	return am_i_win(game, x, y);
}

void Player::reset()
{
	attacks.clear();
	defends.clear();
}