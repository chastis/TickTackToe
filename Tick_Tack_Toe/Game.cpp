#include "Game.h"
#include <iostream>

Game::Game(size_t n)
{
	_playing = true;
	_win_points = 3;
	_first_p_turn = true;
	//sfml staff
	_texture.loadFromFile("images/xo.png");
	//sglazhivanie
	_texture.setSmooth(true);
	_sprite.setTexture(_texture);


	//by task
	_size = n;
	_prev_size = n;
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
			else std::cout << "x";
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
			if (_field[i][j] == cell::empty) _sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
			if (_field[i][j] == cell::o) _sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
			if (_field[i][j] == cell::x)  _sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
			_sprite.setPosition(i * 32, j * 32);
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