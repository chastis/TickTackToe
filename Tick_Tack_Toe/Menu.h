#ifndef MENU_H
#define MENU_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include "Game.h"

class Buttons
{
public:
	friend class Menu;
	Buttons();
	~Buttons();
	Buttons(std::string name, int x, int y, bool visible = false);
	bool is_visible();
	bool contain(int x, int y);
	void draw(sf::RenderWindow &window);
	void print_pos();
	bool is_shine();
private:
	void change_color();
	void shine_color();
	void return_color();
	std::string _name;
	sf::Texture _texture;
	sf::Sprite _sprite;
	bool _visible;
	bool _shine;
};

class Menu
{
public:
	Menu();
	~Menu();
	bool is_menu();
	void open();
	void close();
	void change_colors(sf::Vector2f pos);
	void draw(sf::RenderWindow &window, Game &game);
	void work(sf::Vector2f pos, sf::RenderWindow &window, Game &game);
	void reset();
private:
	//menu are showing
	bool _is_menu;
	bool _is_game;
	//sfml staff
	std::vector<Buttons * > _buttons;
};

#endif // !MENU_H
