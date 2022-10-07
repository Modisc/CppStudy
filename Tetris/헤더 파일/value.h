#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <list>

#include "Macro.h"
#include "Flags.h"

#define STAGE_WIDTH (10)
#define STAGE_HEIGHT (15)

using std::cout;
using std::cin;
using std::endl;
using std::list;

struct Position
{
	int x;
	int y;

	Position(): x(0), y(0)
	{

	}

	Position(const Position& pos)
	{
		*this = pos;
	}

	Position(int _x, int _y) : x(_x), y(_y)
	{

	}

	Position operator +(const Position& pos)
	{
		Position p;
		p.x = x + pos.x;
		p.y = y + pos.y;
		return p;
	}

	Position operator +(int i)
	{
		Position p;
		p.x = x + i;
		p.y = y + i;
		return p;
	}

	void operator +=(const Position& pos)
	{
		x += pos.x;
		y += pos.y;
	}

	void operator +=(int i)
	{
		x += i;
		y += i;
	}

	Position operator -(const Position& pos)
	{
		Position p;
		p.x = x - pos.x;
		p.y = y - pos.y;
		return p;
	}

	Position operator -(int i)
	{
		Position p;
		p.x = x - i;
		p.y = y - i;
		return p;
	}

	void operator -=(const Position& pos)
	{
		x -= pos.x;
		y -= pos.y;
	}

	void operator -=(int i)
	{
		x -= i;
		y -= i;
	}

	// 구조체 대입 연산자는 굳이 operator로 정의해주지 않아도 원래 가능함.
	/*void operator =(const Position& pos)
	{
		x = pos.x;
		y = pos.y;
	}*/
};