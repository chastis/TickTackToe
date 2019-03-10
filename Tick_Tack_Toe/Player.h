#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"
#include <SFML\Graphics.hpp>
#include <vector>

enum class lines_type
{
	horizontal, vertical, bot_right_top_left, bot_left_top_right, point
};

//points
struct Point
{
	Point(int _x = 0, int _y = 0);
	int x;
	int y;
	
};
//line of point
struct Line
{
	Line();
	Line(int x1, int y1, int x2, int y2);
	void add_point(Point p);
	bool touch(Point p, Point &touch_point);
	void print();
	Point start;
	Point end;
	int len;
	lines_type type;
};

class Player
{
public:
	friend class Menu;
	Player();
	//are you a bot?
	//cell that you would to play
	Player(bool is_bot, cell my_cell);
	~Player();
	//turn of player
	bool make_turn(Game &game, sf::Vector2f pos);
	//ai turn
	bool make_ai_turn(Game &game);
	//are you a bot?
	bool is_bot();
	//reset to start;
	void reset();

private:
	//check for win
	bool am_i_win(Game &game, size_t x, size_t y);
	//cell of this player
	cell _my_cell;
	//is this bot?
	bool _is_bot;
	//enemys line
	std::vector<Line> defends;
	//my line
	std::vector<Line> attacks;
	
};

const bool operator <(const Point &a, const Point &b);

const bool operator ==(const Point &a, const Point &b);

void merge(std::vector<Line> &lines);

#endif // !PLAYER_H
