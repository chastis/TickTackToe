#include "Game.h"

//size of cell in px
#define CELL_SIZE 160

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