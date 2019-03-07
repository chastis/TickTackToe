#ifndef GAME_H
#define GAME_H

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
	Game(size_t n = 8);
	~Game();
	//are we still playing?
	bool playing();
	//print to cmd
	void print();

private:
	//the field itself
	cell** _field;
	//width and height of the field
	size_t _size;
	//???
	bool _playing;
};

#endif // !GAME_H
