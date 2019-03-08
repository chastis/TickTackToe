#ifndef MESSAGE_H
#define MESSAGE_H
#include "SFML\Graphics.hpp"

class Message
{
public:
	bool x_won;
	bool o_won;
	Message();
	~Message();
	void draw_x_won(sf::RenderWindow &window);
	void draw_o_won(sf::RenderWindow &window);
private:
	sf::Texture _texture_x;
	sf::Sprite _sprite_x;
	sf::Texture _texture_o;
	sf::Sprite _sprite_o;
};
#endif // !MESSAGE_H
