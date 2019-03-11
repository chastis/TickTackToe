#include "Game.h"
#include <iostream>

//size of cell in px
#define CELL_SIZE 160

void merge(std::vector<Attack> &lines)
{

	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = i + 1; j < lines.size(); j++)
		{
			if (lines[i].line.end == lines[j].line.start && lines[i].line.type == lines[j].line.type)
			{
				lines[i].line.end = lines[j].line.end;
				lines[i].line.len += lines[j].line.len - 1;
				lines.erase(lines.begin() + j);
				i--;
				break;
			}
			if (lines[i].line.start == lines[j].line.end && lines[i].line.type == lines[j].line.type)
			{
				lines[i].line.start = lines[j].line.start;
				lines[i].line.len += lines[j].line.len - 1;
				lines.erase(lines.begin() + j);
				i--;
				break;
			}
		}

	}
}

int amount_nearby_cell(Game &game, int x, int y, cell this_cell)
{
	int answer = 0;
	if (x != 0 && game._field[x - 1][y] == this_cell)
		answer++;
	if (x != game._size - 1 && game._field[x + 1][y] == this_cell)
		answer++;
	if (y != 0 && game._field[x][y - 1] == this_cell)
		answer++;
	if (y != game._size - 1 && game._field[x][y + 1] == this_cell)
		answer++;
	if (x != 0 && y != 0 && game._field[x - 1][y - 1] == this_cell)
		answer++;
	if (x != game._size - 1 && y != 0 && game._field[x + 1][y - 1] == this_cell)
		answer++;
	if (x != 0 && y != game._size - 1 && game._field[x - 1][y + 1] == this_cell)
		answer++;
	if (x != game._size - 1 && y != game._size - 1 && game._field[x + 1][y + 1] == this_cell)
		answer++;
	return answer;
}

int count_weight(std::vector<Attack>& attacks, int x, int y, int win_points)
{
	int max_w = 0;
	int count_of_fork = 0;
	for (int i = 0; i < attacks.size(); i++)
	{
		
		int temp_w = 0;
		if (attacks[i].is_content(x, y))
		{
			if (attacks[i].potential == 2 && attacks[i].line.len == win_points - 2 || 
				attacks[i].potential == 1 && attacks[i].line.len == win_points - 1 ||
				attacks[i].space == 1 && attacks[i].line.len == win_points - 2 )
			{
				count_of_fork++;
			}
			if (attacks[i].line.type == lines_type::point)
			{
				if (temp_w < 1) temp_w = 1;
			}
			else
			{
				if (attacks[i].line.len == win_points)
				{
					temp_w = 99999;
				}
				else if (attacks[i].line.len == win_points - 1 && attacks[i].potential != 0)
				{
					if (attacks[i].potential == 2)
					{
						temp_w = 10000;
					}
					else
					{
						1000;
					}
				}
				else
				{
					temp_w = attacks[i].line.len * attacks[i].line.len * 100 * attacks[i].potential;
					if (attacks[i].space > 0) temp_w += 200 / attacks[i].space;
				}
			}
		}
		
		max_w += temp_w;
	}
	if (count_of_fork >= 1)
	{
		max_w += count_of_fork * 1001;
	}
	if (max_w > 99999) max_w = 99999;
	return max_w;
}

Attack::Attack()
{
	line;
	potential = -42;
	space = -42;
}

Attack::Attack(Game& game, int x1, int y1, int x2, int y2, cell my_cell)
{
	{
		Line temp(x1, y1, x2, y2);
		line = temp;
	}
	potential = 8;
	space = -42;
	if (line.type == lines_type::point)
	{
		Point p(line.start.x, line.start.y);
		if (p.x == 0 || game._field[p.x - 1][p.y] != cell::empty)
			potential--;
		if (p.x == game._size - 1 || game._field[p.x + 1][p.y] != cell::empty)
			potential--;
		if (p.y == 0 || game._field[p.x][p.y - 1] != cell::empty)
			potential--;
		if (p.y == game._size - 1 || game._field[p.x][p.y + 1] != cell::empty)
			potential--;
		if (p.x == 0 || p.y == 0 || game._field[p.x - 1][p.y - 1] != cell::empty)
			potential--;
		if (p.x == game._size - 1 || p.y == 0 || game._field[p.x + 1][p.y - 1] != cell::empty)
			potential--;
		if (p.x == 0 || p.y == game._size - 1 || game._field[p.x - 1][p.y + 1] != cell::empty)
			potential--;
		if (p.x == game._size - 1 || p.y == game._size - 1 || game._field[p.x + 1][p.y + 1] != cell::empty)
			potential--;
	}
	else
	{
		//this cannot happen!!!
		std::cout << "NANI1\n";
	}
}

void Attack::update(Game &game, cell my_cell)
{
	potential = 2;
	space = -42;
	switch (line.type)
	{
	case lines_type::vertical: 
	{
		//check attack place
		//start pos
		int temp_x = line.start.x, temp_y = line.start.y;
		//we already have some points
		int attack_place = line.len;
		//space to next attack
		int temp_space = 0;
		//search
		while (temp_y != 0)
		{
			temp_y--;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				attack_place++;
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		//start pos
		temp_x = line.end.x; temp_y = line.end.y;
		//space to next attack
		temp_space = 0;
		while (temp_y != game._size - 1)
		{
			temp_y++;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				attack_place++;
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		if (attack_place < game._win_points)
		{
			potential = 0;
			break;
		}
		//check limits
		if (line.start.y == 0 || game._field[line.start.x][line.start.y - 1] != cell::empty)
			potential--;
		if (line.end.y == game._size - 1 || game._field[line.end.x][line.end.y + 1] != cell::empty)
			potential--;
		break;
	}
	case lines_type::horizontal:
	{
		//check attack place
		//start pos
		int temp_x = line.start.x, temp_y = line.start.y;
		//we already have some points
		int attack_place = line.len;
		//space to next attack
		int temp_space = 0;
		//search
		while (temp_x != 0)
		{
			temp_x--;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				attack_place++;
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		//start pos
		temp_space = 0;
		temp_x = line.end.x; temp_y = line.end.y;
		while (temp_x != game._size - 1)
		{
			temp_x++;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				attack_place++;
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		if (attack_place < game._win_points)
		{
			potential = 0;
			break;
		}
		//check limits
		if (line.start.x == 0 || game._field[line.start.x - 1][line.start.y] != cell::empty)
			potential--;
		if (line.end.x == game._size - 1 || game._field[line.end.x + 1][line.end.y] != cell::empty)
			potential--;
		break;
	}
	case lines_type::bot_left_top_right:
	{
		//check attack place
		//start pos
		int temp_x = line.start.x, temp_y = line.start.y;
		//we already have some points
		int attack_place = line.len;
		//space to next attack
		int temp_space = 0;
		//search
		while (temp_x != 0 && temp_y != game._size - 1)
		{
			temp_y++;
			temp_x--;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				attack_place++;
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		//start pos
		temp_space = 0;
		temp_x = line.end.x; temp_y = line.end.y;
		while (temp_x != game._size - 1 && temp_y != 0)
		{
			temp_y--;
			temp_x++;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				attack_place++;
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		if (attack_place < game._win_points)
		{
			potential = 0;
			break;
		}
		//check limits
		if (line.start.x == 0  || line.start.y == game._size - 1 || game._field[line.start.x - 1][line.start.y + 1] != cell::empty)
			potential--;
		if (line.end.x == game._size - 1 || line.end.y == 0 || game._field[line.end.x + 1][line.end.y - 1] != cell::empty)
			potential--;
		break;
	}
	case lines_type::bot_right_top_left:
	{
		//check attack place
		//start pos
		int temp_x = line.start.x, temp_y = line.start.y;
		//we already have some points
		int attack_place = line.len;
		//space to next attack
		int temp_space = 0;
		//search
		while (temp_y != 0 && temp_x != 0)
		{
			temp_y--;
			temp_x--;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				attack_place++;
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		//start pos
		temp_space = 0;
		temp_x = line.end.x; temp_y = line.end.y;
		while (temp_y != game._size - 1 && temp_x != game._size - 1)
		{
			temp_y++;
			temp_x++;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				attack_place++;
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		if (attack_place < game._win_points)
		{
			potential = 0;
			break;
		}
		if (line.start.x == 0 || line.start.y == 0 || game._field[line.start.x - 1][line.start.y - 1] != cell::empty)
			potential--;
		if (line.end.x == game._size - 1 || line.end.y == game._size - 1 || game._field[line.end.x + 1][line.end.y + 1] != cell::empty)
			potential--;
		break;
	}
	case lines_type::point:
	{
		
		potential = 8;
		Point p(line.start.x, line.start.y);
		if (p.x == 0 || game._field[p.x - 1][p.y] != cell::empty)
			potential--;
		if (p.x == game._size - 1 || game._field[p.x + 1][p.y] != cell::empty)
			potential--;
		if (p.y == 0 || game._field[p.x][p.y - 1] != cell::empty)
			potential--;
		if (p.y == game._size - 1 || game._field[p.x][p.y + 1] != cell::empty)
			potential--;
		if (p.x == 0 || p.y == 0 || game._field[p.x - 1][p.y - 1] != cell::empty)
			potential--;
		if (p.x == game._size - 1 || p.y == 0 || game._field[p.x + 1][p.y - 1] != cell::empty)
			potential--;
		if (p.x == 0 || p.y == game._size - 1 || game._field[p.x - 1][p.y + 1] != cell::empty)
			potential--;
		if (p.x == game._size - 1 || p.y == game._size - 1 || game._field[p.x + 1][p.y + 1] != cell::empty)
			potential--;
		//space to next attack
		int temp_space = 0;
		//start pos
		int temp_x = line.start.x, temp_y = line.start.y;
		///search vertical
		while (temp_y != 0)
		{
			temp_y--;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		//start pos
		temp_x = line.end.x; temp_y = line.end.y;
		temp_space = 0;
		while (temp_y != game._size - 1)
		{
			temp_y++;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		

		///search horizontal
		//start pos
		temp_space = 0;
		temp_x = line.end.x; temp_y = line.end.y;
		while (temp_x != 0)
		{
			temp_x--;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		//start pos
		temp_space = 0;
		temp_x = line.end.x; temp_y = line.end.y;
		while (temp_x != game._size - 1)
		{
			temp_x++;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}

		///search from bottom left to top right
		//start pos
		temp_space = 0;
		temp_x = line.end.x; temp_y = line.end.y;
		while (temp_x != 0 && temp_y != game._size - 1)
		{
			temp_y++;
			temp_x--;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		//start pos
		temp_space = 0;
		temp_x = line.end.x; temp_y = line.end.y;
		while (temp_x != game._size - 1 && temp_y != 0)
		{
			temp_y--;
			temp_x++;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}

		///search from bottom right to top left
		//start pos
		temp_space = 0;
		temp_x = line.end.x; temp_y = line.end.y;
		while (temp_y != 0 && temp_x != 0)
		{
			temp_y--;
			temp_x--;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		//start pos
		temp_space = 0;
		temp_x = line.end.x; temp_y = line.end.y;
		while (temp_y != game._size - 1 && temp_x != game._size - 1)
		{
			temp_y++;
			temp_x++;
			if (game._field[temp_x][temp_y] == cell::empty)
			{
				temp_space++;
			}
			else
			{
				if (game._field[temp_x][temp_y] == my_cell)
					if (temp_space != 0 && (space <= 0 || temp_space < space))
						space = temp_space;
				break;
			}
		}
		break;
	}
	}

}

void Attack::print()
{
	line.print();
	std::cout << " p: " << potential << " s: " << space << std::endl;
}

bool Attack::is_content(int x, int y)
{
	switch (line.type)
	{
	case lines_type::horizontal:
	{
		if (line.start.y == y && line.start.x <= x && line.end.x >= x) return true;
		else return false;
	}
	case lines_type::vertical:
	{
		if (line.start.x == x && line.start.y <= y && line.end.y >= y) return true;
		else return false;
	}
	case lines_type::bot_left_top_right:
	{
		if (x - line.start.x == line.start.y - y && line.end.x - x == y - line.end.y) return true;
		else return false;
	}
	case lines_type::bot_right_top_left:
	{
		if (x - line.start.x == y - line.start.y && line.end.x - x == line.end.y - y) return true;
		else return false;
	}
	case lines_type::point:
	{
		if (x == line.start.x && y == line.start.y) return true;
		else return false;
	}
	}
	return false;
}

Game::Game(size_t n)
{
	_playing = true;
	_first_p_turn = true;
	//we don't have latest point
	_last_x = 42;
	_last_y = 42;
	//sfml staff
	_texture.loadFromFile("images/xo6.png");
	_sprite.setTexture(_texture);

	//by task
	_size = n;
	_turns = _size * _size;
	_win_points = _size <= 3 ? _size : _size < 8 ? 3 : _size > 11 ? 5 : 4;
	_prev_size = n;

	//scale's staff
	x_scale = y_scale = (float) 640 / (_size * CELL_SIZE);
	_sprite.setScale(x_scale, y_scale);

	//release memory
	_field = new cell* [_size];
	for (size_t i = 0; i < _size; i++)
	{
		_field[i] = new cell[_size];
	}
	//initialization
	for (size_t i = 0; i < _size; i++)
	{
		for (size_t j = 0; j < _size; j++)
		{
			_field[i][j] = cell::empty;
		}
	}
}

Game::~Game()
{
	//discharge memory
	for (size_t i = 0; i < _size; i++)
	{
		delete[] _field[i];
	}
	delete[] _field;
}

bool Game::playing()
{
	//case for "nobody win"
	if (_turns == 0) return false;
	return _playing;
}

void Game::draw(sf::RenderWindow &window)
{
	
	for (size_t i = 0; i < _size; i++)
	{
		for (size_t j = 0; j < _size; j++)
		{
			//cut our textures
			if (_field[i][j] == cell::empty) _sprite.setTextureRect(sf::IntRect(2 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));

			//!!
			//la béquille
			// there are some truble with scale
			//this make picture more fancy
			//!!

			if (_field[i][j] == cell::o || _field[i][j] == cell::win_o)
				if (_size % 2 == 0)
					_sprite.setTextureRect(sf::IntRect(CELL_SIZE - 1, 0, CELL_SIZE, CELL_SIZE));
				else
					_sprite.setTextureRect(sf::IntRect(CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
			//
			if (_field[i][j] == cell::x || _field[i][j] == cell::win_x)  _sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
			

			//painting cell into purple, if this is winning line
			if (_field[i][j] == cell::win_x || _field[i][j] == cell::win_o)
			{
				_sprite.setColor(sf::Color(140, 102, 255));
			}
			//painting cell into yellow, if this latest put cell
			else if (_last_x == i && _last_y == j)
			{
				_sprite.setColor(sf::Color(255, 255, 153));
			}
			else //return color back;
			{
				_sprite.setColor(sf::Color::White);
			}
			//put in correct place
			_sprite.setPosition(i * CELL_SIZE * x_scale, j * CELL_SIZE * y_scale);
			window.draw(_sprite);
		}	
	}
	
}

bool Game::will_first_go()
{
	return _first_p_turn;
}

void Game::reset()
{
	_playing = true;
	_win_points = _size <= 3 ? _size : _size < 8 ? 3 : _size > 11 ? 5 : 4;
	_turns = _size * _size;
	_first_p_turn = true;
	//we don't have latest point
	_last_x = 42;
	_last_y = 42;
	//reset players
	_p1_attacks.clear();
	_p2_attacks.clear();
	//scale's staff
	x_scale = y_scale = (float) 640 / (_size * CELL_SIZE);
	_sprite.setScale(x_scale, y_scale);

	//discharge prev memory
	for (size_t i = 0; i < _prev_size; i++)
	{
		delete[] _field[i];
	}
	delete _field;

	//release memory
	_field = new cell*[_size];
	for (size_t i = 0; i < _size; i++)
	{
		_field[i] = new cell[_size];
	}
	//initialization
	for (size_t i = 0; i < _size; i++)
	{
		for (size_t j = 0; j < _size; j++)
		{
			_field[i][j] = cell::empty;
		}
	}
	//update prev size
	_prev_size = _size;
}