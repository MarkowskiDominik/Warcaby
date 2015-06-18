#pragma once
#include <algorithm>
#include <random>
#include "Board.h"
#include "Move.h"

class AI
{
	Move bestMove;
	int max_depth;	//depth search tree
	bool mode;		//0 - min-max, 1 - alpha-beta
	int search_order; //0 - left to right, 1 - sort by value
	long long int numberNodes = 0;
	int minmax(Board, bool, int);
	int alphabeta(Board, bool, int, int, int);

public:
	AI();
	AI(int, bool, int);
	~AI();

	Move& search(Board, bool);
	long long int getNumberNodes() { return numberNodes; }
};