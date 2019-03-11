#include <time.h>
#include "Menu.h"
#include "Game.h"
#include "Player.h"


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
	//take center
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
//turquoise
void Buttons::change_color()
{
	_sprite.setColor(sf::Color(102,255,153));
}
//purple
void Buttons::shine_color()
{
	_sprite.setColor(sf::Color(140, 102, 255));
}
//white
void Buttons::return_color()
{
	if (_sprite.getColor() != sf::Color::White) _sprite.setColor(sf::Color::White);
}

void Buttons::draw(sf::RenderWindow &window)
{
	window.draw(_sprite);
}

bool Buttons::is_shine()
{
	return _shine;
}

Menu::Menu()
{
	_is_menu = true;
	Buttons * b_exit = new Buttons("exit.png", 320, 400, true);
	Buttons * b_new_game = new Buttons("newgame.png", 320, 200, true);
	Buttons * b_pvp = new Buttons("pvp2.png", 320, 300);
	b_pvp->_shine = true; b_pvp->shine_color();
	Buttons * b_eve = new Buttons("eve2.png", 165, 300);
	Buttons * b_pve = new Buttons("pve2.png", 475, 300);
	Buttons * b_mapssize = new Buttons("mapssize3.png", 320, 200);
	Buttons * b_start = new Buttons("start.png", 320, 400);
	Buttons * b_left = new Buttons("left.png", 135, 200);
	Buttons * b_right = new Buttons("right.png", 508 , 200);
	Buttons * b_b_rules = new Buttons("buttonrules.png", 320, 300, true);
	Buttons * b_rules = new Buttons("rules.png", 320, 320);
	_buttons.push_back(b_exit);//0
	_buttons.push_back(b_new_game);//1
	_buttons.push_back(b_pvp);//2
	_buttons.push_back(b_eve);//3
	_buttons.push_back(b_pve);//4
	_buttons.push_back(b_mapssize);//5
	_buttons.push_back(b_start);//6
	_buttons.push_back(b_left);//7
	_buttons.push_back(b_right);//8
	_buttons.push_back(b_b_rules);//9
	_buttons.push_back(b_rules);//9
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
	reset();
}

void Menu::close()
{
	_is_menu = false;
}

void Menu::draw(sf::RenderWindow &window, Game &game)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->is_visible())
		{
			//da budet svet
			if (_buttons[i]->is_shine()) _buttons[i]->shine_color();
			_buttons[i]->draw(window);
		}
	}
	//additional text
	if (_buttons[5]->is_visible())
	{
		//put text
		//size of the game field
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
		//button 5 is "map's size". it;s not a button!!!
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
			//new game //0
			//ext //1
			_buttons[i]->_visible = true;
		else
			//another are not visible
			_buttons[i]->_visible = false;
	}
	//rules //9
	_buttons[9]->_visible = true;
}

void Menu::work(sf::Vector2f pos, sf::RenderWindow &window, Game &game, Player &p1, Player &p2)
{
	//button's functions
	auto to_do = [&](int n)
	{
		switch (n)
		{
			//exit
			case 0: 
			{
				//game.~Game();
				window.close();
				
				break;
			}
			//newgame
			case 1:
			{
				//go second page
				_buttons[0]->_visible = false;
				_buttons[1]->_visible = false;
				_buttons[9]->_visible = false;
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
				//change game settings
				p1._is_bot = false;
				p2._is_bot = false;
				break;
			}
			//eve
			case 3:
			{
				_buttons[2]->_shine = false;
				_buttons[3]->_shine = true;
				_buttons[4]->_shine = false;
				//change game settings
				p1._is_bot = true;
				p2._is_bot = true;
				break;
			}
			//pve
			case 4:
			{
				_buttons[2]->_shine = false;
				_buttons[3]->_shine = false;
				_buttons[4]->_shine = true;
				//change game settings
				std::srand(std::time(0));
				p1._is_bot = rand() % 2;
				//p1._is_bot = true;
				p2._is_bot = !p1.is_bot();
				
				break;
			}
			//start
			case 6:
			{
				//rerandom every time
				if (_buttons[4]->is_shine())
				{
					//change game settings
					std::srand(std::time(0));
					p1._is_bot = rand() % 2;
					//p1._is_bot = true;
					p2._is_bot = !p1.is_bot();
				}
				game.reset();
				this->close();
				break;
			}
			//left
			case 7:
			{
				//game's field size --
				if (game._size != 1) game._size--;
				break;
			}
			//right
			case 8:
			{
				//game's field size ++
				if (game._size != 15) game._size++;
				break;
			}
			//button rules
			case 9:
			{
				//open rules
				_buttons[0]->_visible = false;
				_buttons[1]->_visible = false;
				_buttons[9]->_visible = false;
				_buttons[10]->_visible = true;
				break;
			}
			//rules by itself
			case 10:
			{
				//return to home page
				_buttons[0]->_visible = true;
				_buttons[1]->_visible = true;
				_buttons[9]->_visible = true;
				_buttons[10]->_visible = false;
			}
		}
	
	};
	for (int i = 0; i < _buttons.size(); i++)
	{
		//if we presssed correct button, let it work
		if (_buttons[i]->is_visible() && _buttons[i]->contain(pos.x, pos.y))
		{
			to_do(i);
			return;
		}
	}
}