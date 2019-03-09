#ifndef MESSAGE_H
#define MESSAGE_H
#include "SFML\Graphics.hpp"
#include "Menu.h"

class Msg_Buttons : Buttons
{
public:
	friend class Message;
	Msg_Buttons();
	Msg_Buttons(std::string name, std::string external_name, int x, int y, bool visible = false);
	void set(std::string name, std::string external_name, int x, int y, bool visible = false);
private:
	//external pictures
	//original one in parent
	sf::Texture _external_texture;
	sf::Sprite _external_sprite;
};

class Message
{
public:
	//is x winner?
	bool x_won;
	//is o winner?
	bool o_won;
	//does message show?
	bool is_message();
	Message();
	~Message();
	//draw and repaint
	void draw_won(sf::Vector2f pos, sf::RenderWindow &window);
	//check for pressed
	bool work(sf::Vector2f pos);
	//close msg window
	void close();
private:
	//does message show?
	bool _is_message;
	//two buttons
	Msg_Buttons _about_x;
	Msg_Buttons _about_o;
};
#endif // !MESSAGE_H
