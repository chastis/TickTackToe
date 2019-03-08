#include "Game.h"
#include <iostream>

#define CELL_SIZE 160

Game::Game(size_t n)
{
	//if (n == 8) std::cout << "Hello there!" << std::endl;
	_playing = true;
	_first_p_turn = true;
	//sfml staff
	_texture.loadFromFile("images/xo6.png");
	//sglazhivanie
	//_texture.setSmooth(true);
	_sprite.setTexture(_texture);

	//by task
	_size = n;
	_win_points = _size <= 3 ? _size : _size < 8 ? 3 : _size > 11 ? 5 : 4;
	_prev_size = n;

	//scale's staff
	x_scale = y_scale = (float) 640 / (_size * CELL_SIZE);
	//std::cout << x_scale << " " << y_scale << std::endl;
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
	return _playing;
}

void Game::print()
{
	for (size_t i = 0; i < _size; i++)
	{
		for (size_t j = 0; j < _size; j++)
		{
			if (_field[i][j] == cell::empty) std::cout << "*";
			else if (_field[i][j] == cell::o) std::cout << "o";
			else if (_field[i][j] == cell::x) std::cout << "x";
			else if (_field[i][j] == cell::win_x) std::cout << "%";
			else std::cout << "@";
		}
		std::cout << std::endl;
	}
}

void Game::draw(sf::RenderWindow &window)
{
	
	for (size_t i = 0; i < _size; i++)
	{
		for (size_t j = 0; j < _size; j++)
		{
			if (_field[i][j] == cell::empty) _sprite.setTextureRect(sf::IntRect(2 * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
			//la béquille
			// there are some truble with scale
			if (_field[i][j] == cell::o || _field[i][j] == cell::win_o)
				if (_size % 2 == 0)
					_sprite.setTextureRect(sf::IntRect(CELL_SIZE - 1, 0, CELL_SIZE, CELL_SIZE));
				else
					_sprite.setTextureRect(sf::IntRect(CELL_SIZE, 0, CELL_SIZE, CELL_SIZE));
			//
			if (_field[i][j] == cell::x || _field[i][j] == cell::win_x)  _sprite.setTextureRect(sf::IntRect(0, 0, CELL_SIZE, CELL_SIZE));
			
			if (_field[i][j] == cell::win_x || _field[i][j] == cell::win_o)
			{
				_sprite.setColor(sf::Color(140, 102, 255));
			}
			else
			{
				_sprite.setColor(sf::Color::White);
			}
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
	_first_p_turn = true;
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

	_prev_size = _size;
}