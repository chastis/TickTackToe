#include "Line.h"
#include <iostream>

const bool operator <(const Point &a, const Point &b)
{
	if (a.x < b.x) return true;
	else if (a.x > b.x) return false;
	else return (a.y < b.y);

}

const bool operator ==(const Point &a, const Point &b)
{
	if (a.x == b.x && a.y == b.y) return true; else return false;
}

void merge(std::vector<Line> &lines)
{

	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = i + 1; j < lines.size(); j++)
		{
			if (lines[i].end == lines[j].start && lines[i].type == lines[j].type)
			{
				lines[i].end = lines[j].end;
				lines[i].len += lines[j].len - 1;
				lines.erase(lines.begin() + j);
				i--;
				break;
			}
			if (lines[i].start == lines[j].end && lines[i].type == lines[j].type)
			{
				lines[i].start = lines[j].start;
				lines[i].len += lines[j].len - 1;
				lines.erase(lines.begin() + j);
				i--;
				break;
			}
		}

	}
}

Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

Line::Line()
{
	start;
	end;
	len = 0;
	type = lines_type::point;
}

Line::Line(int x1, int y1, int x2, int y2)
{
	if (x1 < x2)
	{
		start.x = x1;
		start.y = y1;
		end.x = x2;
		end.y = y2;
	}
	else if (x2 < x1)
	{
		start.x = x2;
		start.y = y2;
		end.x = x1;
		end.y = y1;
	}
	else if (y1 < y2)
	{
		start.x = x1;
		start.y = y1;
		end.x = x2;
		end.y = y2;
	}
	else
	{
		start.x = x2;
		start.y = y2;
		end.x = x1;
		end.y = y1;
	}

	len = std::abs(x2 - x1) > std::abs(y2 - y1) ? std::abs(x2 - x1) + 1 : std::abs(y2 - y1) + 1;
	if (len == 1)
	{
		type = lines_type::point;
	}
	else
	{
		if (start.x == end.x) type = lines_type::vertical;
		else if (start.y == end.y) type = lines_type::horizontal;
		else if (start.y > end.y) type = lines_type::bot_left_top_right;
		else type = lines_type::bot_right_top_left;
	}
}

void Line::print()
{
	std::cout << "(" << start.x << " " << start.y << ") (" << end.x << " " << end.y << ")" << std::endl;
}

void Line::add_point(Point p)
{
	{
		//horiontal line
		if (start.y == end.y)
		{
			if (start.x != 0 && start.y == p.y && p.x == start.x - 1)
			{
				start.x--;
				len++;
				type = lines_type::horizontal;
				return;
			}
			if (end.y == p.y && p.x == end.x + 1)
			{
				end.x++;
				len++;
				type = lines_type::horizontal;
				return;
			}
		}
		//vertical
		if (start.x == end.x)
		{
			if (start.y != 0 && start.x == p.x && p.y == start.y - 1)
			{
				start.y--;
				len++;
				type = lines_type::vertical;
				return;
			}
			if (end.x == p.x && p.y == end.y + 1)
			{
				end.y++;
				len++;
				type = lines_type::vertical;
				return;
			}
		}
		//diagonal
		//from bottom left to top right
		if (len == 1 || start.x < end.x && start.y > end.y)
		{
			if (start.x - 1 == p.x && p.y == start.y + 1)
			{
				start.x--;
				start.y++;
				len++;
				type = lines_type::bot_left_top_right;
				return;
			}
			if (end.y != 0 && end.x + 1 == p.x && p.y == end.y - 1)
			{
				end.x++;
				end.y--;
				len++;
				type = lines_type::bot_left_top_right;
				return;
			}
		}
		//from bottom right to top left
		if (len == 1 || start.x < end.x && start.y < end.y)
		{
			if (start.y != 0 && start.x != 0 && start.x - 1 == p.x && p.y == start.y - 1)
			{
				start.x--;
				start.y--;
				len++;
				type = lines_type::bot_right_top_left;
				return;
			}
			if (end.x + 1 == p.x && p.y == end.y + 1)
			{
				end.x++;
				end.y++;
				len++;
				type = lines_type::bot_right_top_left;
				return;
			}
		}
	}
}

bool Line::touch(Point p, Point &touch_point)
{
	//horizontal line
	if (start.y == end.y)
	{
		if (start.x != 0 && start.y == p.y && p.x == start.x - 1)
		{
			touch_point = start;
			return true;
		}
		else if (end.y == p.y && p.x == end.x + 1)
		{
			touch_point = end;
			return true;
		}
	}
	//vertical
	if (start.x == end.x)
	{
		if (start.y != 0 && start.x == p.x && p.y == start.y - 1)
		{
			touch_point = start;
			return true;
		}
		else if (end.x == p.x && p.y == end.y + 1)
		{
			touch_point = end;
			return true;
		}
	}
	//diagonal
	//from bottom left to top right
	if (len == 1 || start.x < end.x && start.y > end.y)
	{
		if (start.x - 1 == p.x && p.y == start.y + 1)
		{
			touch_point = start;
			return true;
		}
		else if (end.y != 0 && end.x + 1 == p.x && p.y == end.y - 1)
		{
			touch_point = end;
			return true;
		}
	}
	//from bottom right to top left
	if (len == 1 || start.x < end.x && start.y < end.y)
	{
		if (start.y != 0 && start.x != 0 && start.x - 1 == p.x && p.y == start.y - 1)
		{
			touch_point = start;
			return true;
		}
		else if (end.x + 1 == p.x && p.y == end.y + 1)
		{
			touch_point = end;
			return true;
		}
	}
	return false;
}
