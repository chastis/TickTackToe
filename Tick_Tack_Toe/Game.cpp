#include "Game.h"
#include <iostream>

Game::Game(size_t n)
{
	_playing = true;
	_win_points = 3;

	//by task
	_size = n;
	//release memory
	_field = new cell* [_size];
	for (int i = 0; i < _size; i++)
	{
		_field[i] = new cell[_size];
	}
	//initialization
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			_field[i][j] = cell::empty;
		}
	}
}
Game::~Game()
{
	//discharge memory
	for (int i = 0; i < _size; i++)
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
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_field[i][j] == cell::empty) std::cout << "*";
			else if (_field[i][j] == cell::o) std::cout << "o";
			else std::cout << "x";
		}
		std::cout << std::endl;
	}
}