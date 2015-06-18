#pragma once
#include <cstdlib>
#include <iostream>
#include <list>
#include "Move.h"

using namespace std;

struct Figure
{
	bool player, type;
	Figure(bool _player, bool _type) : player(_player), type(_type) {}
	Figure(Figure* _figure) : player(_figure->player), type(_figure->type) {}
	~Figure() {}
};

class Board
{
	int aFigure = 12;
	int bFigure = 12;
	int evaluateType;
	Figure* fields[8][8];

	bool inBoard(int row, int column) const { return (row > -1 && row < 8 && column > -1 && column < 8); }
	void promotion(int, int);
	int evaluateNumber();
	int evaluateValue();
	int evaluateTactics();
	int priorityP(int, int);
	int priorityD(int, int);
	int security(int, int);

public:
	Board();
	Board(int);
	Board(Board&);
	Board(Board&, Move&);
	~Board();

	void show();
	void create();
	int evaluate();
	void makeMove(Move&);
	int game_over();
	void getMove(bool, std::list<Move>&);
	void getJump(bool, std::list<Move>&);

	Figure*& operator()(int x, int y) { return fields[x][y]; }
};