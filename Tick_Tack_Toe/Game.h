#ifndef GAME_H
#define GAME_H
#include <SFML\Graphics.hpp>

//content of cell in the field
enum class cell
{
	x, o, empty, win_x, win_o
};


class Game
{
public:
	friend class Player;
	friend class Menu;
	//n is size of the field
	Game(size_t n = 8);
	~Game();

	void reset();
	//are we still playing?
	bool playing();
	//print to cmd
	void print();
	//drow with sfml
	void draw(sf::RenderWindow &window);
	//will first player go?
	bool will_first_go();
private:
	//the field itself
	cell** _field;
	//width and height of the field
	size_t _size;
	size_t _prev_size;
	//are we still playing?
	bool _playing;
	//amount points for win
	size_t _win_points;
	//will first player go?
	bool _first_p_turn;

	//scale's param
	float x_scale;
	float y_scale;
	//sfml staff
	sf::Texture _texture;
	sf::Sprite _sprite;
};

#endif // !GAME_H
