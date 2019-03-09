#include "Message.h"

Msg_Buttons::Msg_Buttons()
{
	_name = ""; 
	_texture; _sprite;
	_external_texture; _external_sprite;
}

Msg_Buttons::Msg_Buttons(std::string name, std::string external_name, int x, int y, bool visible)
{
	_visible = visible;
	_shine = false;
	_name = name;
	_texture.loadFromFile("images/" + name);
	_external_texture.loadFromFile("images/" + external_name);
	_sprite.setTexture(_texture);
	_external_sprite.setTexture(_external_texture);
	//take center
	_sprite.setPosition(x - _texture.getSize().x / 2, y - _texture.getSize().y / 2);
	_external_sprite.setPosition(x - _texture.getSize().x / 2, y - _texture.getSize().y / 2);
}

void Msg_Buttons::set(std::string name, std::string external_name, int x, int y, bool visible)
{
	_visible = visible;
	_shine = false;
	_name = name;
	_texture.loadFromFile("images/" + name);
	_external_texture.loadFromFile("images/" + external_name);
	_sprite.setTexture(_texture);
	_external_sprite.setTexture(_external_texture);
	//take center
	_sprite.setPosition(x - _texture.getSize().x / 2, y - _texture.getSize().y / 2);
	_external_sprite.setPosition(x - _texture.getSize().x / 2, y - _texture.getSize().y / 2);
}

Message::Message()
{
	x_won = false;
	o_won = false;
	_about_o.set("owon.png", "tothemenu.png", 320,320);
	//change "to the menu color"
	_about_o._external_sprite.setColor(sf::Color(102, 255, 153));
	_about_x.set("xwon.png", "nobody.png", 320, 320);
}

Message::~Message()
{

}

bool Message::is_message()
{
	return _is_message;
}

void Message::draw_won(sf::Vector2f pos, sf::RenderWindow &window)
{
	//if we here, then messege are showing!
	_is_message = true;
	//if we on button draw "to the menu"
	if (_about_o.contain(pos.x, pos.y))
		window.draw(_about_o._external_sprite);
	//else
	else if (x_won)
		//if x is winner drow that
		window.draw(_about_x._sprite);
	//draw about o
	else if (o_won) window.draw(_about_o._sprite);
	//drow if everyone loses
	else window.draw(_about_x._external_sprite);
}

void Message::close()
{
	//message don't showing anymore
	_is_message = false;
}

bool Message::work(sf::Vector2f pos)
{
	//close message window
	if (_about_o.contain(pos.x, pos.y))
	{
		_is_message = false;
		return true;
	}
	return false;
}