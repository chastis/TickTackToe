#ifndef GAME_H
#define GAME_H
#include <SFML\Graphics.hpp>

//content of cell in the field
enum class cell
{
	x, o, empty
};


class Game
{
public:
	friend class Player;

	//n is size of the field
	Game(size_t n = 3);
	~Game();
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
	//are we still playing?
	bool _playing;
	//amount points for win
	size_t _win_points;
	//will first player go?
	bool _first_p_turn;

	//sfml staff
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

#endif // !GAME_H
