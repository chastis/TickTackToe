#ifndef GAME_H
#define GAME_H
#include <SFML\Graphics.hpp>
#include <vector>
#include "Line.h"

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
	friend class Attack;
	friend std::vector<Attack>& give_attack(Game& game, cell my_cell);
	friend void upgrade_attack(Game& game, cell _my_cell, int x, int y);
	friend int amount_nearby_cell(Game &game, int x, int y, cell this_cell);
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
	std::vector<Attack> _p1_attacks;
	std::vector<Attack> _p2_attacks;
};


class Attack
{
public:
	friend class Player;
	friend void upgrade_attack(Game& game, cell _my_cell, int x, int y);
	friend void upgrade_attack(std::vector<Attack>& attacks, Game& game, cell _my_cell, int x, int y);
	friend void merge(std::vector<Attack> &lines);
	friend int count_weight(std::vector<Attack>& attacks, int x, int y, int win_points);
	Attack();
	Attack(Game &game, int x1, int y1, int x2, int y2, cell my_cell);
	void update(Game &game, cell my_cell);
	void print();
	bool is_content(int x, int y);
private:
	Line line;
	//possibility to continue this attack
	int potential;
	//emty space to next attack (if we have this)
	int space;
};

void merge(std::vector<Attack> &lines);

int amount_nearby_cell(Game &game, int x, int y, cell this_cell);

int count_weight(std::vector<Attack>& attacks, int x, int y, int win_points);
#endif // !GAME_H
