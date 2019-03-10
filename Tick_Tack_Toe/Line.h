#ifndef LINE_H
#define LINE_H
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

const bool operator <(const Point &a, const Point &b);

const bool operator ==(const Point &a, const Point &b);

void merge(std::vector<Line> &lines);

#endif // !LINE_H
