#include "Menu.h"
#include "Game.h"
#include <iostream>

Buttons::Buttons()
{
	_name = "";
	_texture; _sprite;
}

Buttons::~Buttons()
{

}

Buttons::Buttons(std::string name, int x, int y, bool visible)
{
	_visible = visible;
	_shine = false;
	_name = name;
	_texture.loadFromFile("images/" + name);
	_sprite.setTexture(_texture);
	_sprite.setPosition(x - _texture.getSize().x / 2, y - _texture.getSize().y / 2);
}

bool Buttons::is_visible()
{
	return _visible;
}

bool Buttons::contain(int x, int y)
{
	if (_sprite.getPosition().x <= x && x <= _sprite.getPosition().x + _texture.getSize().x &&
		_sprite.getPosition().y <= y && y <= _sprite.getPosition().y + _texture.getSize().y) return true;
	return false;
}

void Buttons::change_color()
{
	_sprite.setColor(sf::Color(102,255,153));
}

void Buttons::shine_color()
{
	_sprite.setColor(sf::Color(140, 102, 255));
}

void Buttons::return_color()
{
	if (_sprite.getColor() != sf::Color::White) _sprite.setColor(sf::Color::White);
}

void Buttons::draw(sf::RenderWindow &window)
{
	window.draw(_sprite);
}

void Buttons::print_pos()
{
	std::cout << _sprite.getPosition().x << " " << _sprite.getPosition().y << " " << _texture.getSize().x << " " << _texture.getSize().y << std::endl;
}

bool Buttons::is_shine()
{
	return _shine;
}

Menu::Menu()
{
	_is_game = true;
	_is_menu = true;
	Buttons * b_exit = new Buttons("exit.png", 320, 300, true);
	Buttons * b_new_game = new Buttons("newgame.png", 320, 200, true);
	//Buttons * b_pvp = new Buttons("pvp.png", 320, 200);
	//Buttons * b_eve = new Buttons("eve.png", 320, 300);
	//Buttons * b_pve = new Buttons("pve.png", 320, 400);
	Buttons * b_pvp = new Buttons("pvp2.png", 320, 300);
	b_pvp->_shine = true; b_pvp->shine_color();
	Buttons * b_eve = new Buttons("eve2.png", 165, 300);
	Buttons * b_pve = new Buttons("pve2.png", 475, 300);
	//Buttons * b_mapssize = new Buttons("mapssize.png", 216, 200);
	Buttons * b_mapssize = new Buttons("mapssize3.png", 320, 200);
	Buttons * b_start = new Buttons("start.png", 320, 400);
	Buttons * b_left = new Buttons("left.png", 135, 200);
	Buttons * b_right = new Buttons("right.png", 508 , 200);
	_buttons.push_back(b_exit);//0
	_buttons.push_back(b_new_game);//1
	_buttons.push_back(b_pvp);//2
	_buttons.push_back(b_eve);//3
	_buttons.push_back(b_pve);//4
	_buttons.push_back(b_mapssize);//5
	_buttons.push_back(b_start);//6
	_buttons.push_back(b_left);//7
	_buttons.push_back(b_right);//8
}

Menu::~Menu()
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		delete _buttons[i];
	}
}

bool Menu::is_menu()
{
	return _is_menu;
}

void Menu::open()
{
	_is_menu = true;
}

void Menu::close()
{
	_is_menu = false;
}

void Menu::draw(sf::RenderWindow &window, Game &game)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		//if (_buttons[i]->_shine) _buttons[i]->change_color(); else _buttons[i]->return_color();
		if (_buttons[i]->is_visible())
		{

			if (_buttons[i]->is_shine()) _buttons[i]->shine_color();
			_buttons[i]->draw(window);
		}
	}
	if (_buttons[5]->is_visible())
	{
		sf::Font font;
		font.loadFromFile("calibri.ttf");
		std::string str;
		str = std::to_string(game._size);
		sf::Text text(str, font, 40);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);
		text.setPosition(420, 168);
		window.draw(text);
	}
}

void Menu::change_colors(sf::Vector2f pos)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->contain(pos.x, pos.y) && i != 5)
		{
			_buttons[i]->change_color();
		}
		else
		{
			_buttons[i]->return_color();
		}
	}
}

void Menu::reset()
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (i <= 1)
			_buttons[i]->_visible = true;
		else
			_buttons[i]->_visible = false;
	}
}

void Menu::work(sf::Vector2f pos, sf::RenderWindow &window, Game &game)
{
	auto to_do = [&](int n)
	{
		switch (n)
		{
			//exit
			case 0: 
			{
				window.close();
				break;
			}
			//newgame
			case 1:
			{
				_buttons[0]->_visible = false;
				_buttons[1]->_visible = false;
				_buttons[2]->_visible = true;
				_buttons[3]->_visible = true;
				_buttons[4]->_visible = true;
				_buttons[5]->_visible = true;
				_buttons[6]->_visible = true;
				_buttons[7]->_visible = true;
				_buttons[8]->_visible = true;
				break;
			}
			//pvp
			case 2:
			{
				_buttons[2]->_shine = true;
				_buttons[3]->_shine = false;
				_buttons[4]->_shine = false;
				break;
			}
			//eve
			case 3:
			{
				_buttons[2]->_shine = false;
				_buttons[3]->_shine = true;
				_buttons[4]->_shine = false;

				break;
			}
			//pve
			case 4:
			{
				_buttons[2]->_shine = false;
				_buttons[3]->_shine = false;
				_buttons[4]->_shine = true;
				break;
			}
			//start
			case 6:
			{
				game.reset();
				this->close();
				break;
			}
			//left
			case 7:
			{
				if (game._size != 1) game._size--;
				break;
			}
			//right
			case 8:
			{
				if (game._size != 15) game._size++;
				break;
			}
		}
	
	};
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->is_visible() && _buttons[i]->contain(pos.x, pos.y))
		{
			to_do(i);
			return;
		}
	}
}