#ifndef GAME_H
#define GAME_H
#include <SFML\Graphics.hpp>
#include <vector>
#include"Line.h"

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

	//reset all game config to start
	void reset();
	//are we still playing?
	bool playing();
	//drow with sfml
	void draw(sf::RenderWindow &window);
	//will first player go?
	bool will_first_go();
private:
	//the field itself
	cell** _field;
	//width and height of the field
	size_t _size;
	//previos size
	size_t _prev_size;
	//are we still playing?
	bool _playing;
	//amount points for win
	size_t _win_points;
	//will first player go?
	bool _first_p_turn;
	//amount of possible turns
	size_t _turns;
	//scale's param
	float x_scale;
	float y_scale;
	//sfml staff
	sf::Texture _texture;
	sf::Sprite _sprite;
	//the latest put point
	size_t _last_x;
	size_t _last_y;
	//attacks of players
	std::vector<Line> _p1_attacks;
	std::vector<Line> _p2_attacks;
};

#endif // !GAME_H
