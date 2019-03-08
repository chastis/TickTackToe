#include "Message.h"

Message::Message()
{
	_texture_x.loadFromFile("images/xwon.png");
	_texture_o.loadFromFile("images/owon.png");
	_sprite_x.setTexture(_texture_x);
	_sprite_o.setTexture(_texture_o);
	x_won = false;
	o_won = false;
	_sprite_x.setPosition(320 - _texture_x.getSize().x / 2, 320 - _texture_x.getSize().y / 2);
	_sprite_o.setPosition(320 - _texture_o.getSize().x / 2, 320 - _texture_o.getSize().y / 2);
}

Message::~Message()
{

}

void Message::draw_x_won(sf::RenderWindow &window)
{
	window.draw(_sprite_x);
}

void Message::draw_o_won(sf::RenderWindow &window)
{
	window.draw(_sprite_o);
}