#include "AI.h"

#include <iostream>
using namespace std;

AI::AI() : max_depth(5), mode(), search_order() {}

AI::AI(int n, bool _mode, int _search_order) : max_depth(n), mode(_mode), search_order(_search_order) {}

AI::~AI() {}

Move& AI::search(Board board, bool player)
{
	numberNodes = 0;
	switch (mode)
	{
	case 0:
		minmax(board, player, 0);
		break;
	case 1:
		alphabeta(board, player, 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
		break;
	} //switch (mode)
	return bestMove;
} //Move& AI::search(Board board, bool player)

int AI::minmax(Board board, bool player, int depth)
{
	numberNodes++;
	if (board.game_over() == 1) return -10000;
	if (board.game_over() == 0) return 10000;
	if (depth == max_depth) return board.evaluate();

	std::list<Move> moves;
	board.getJump(player, moves);
	if (moves.empty()) board.getMove(player, moves);

	if (depth == 0)
	{
		if (player)
		{
			int evaluate = std::numeric_limits<int>::min();
			for each (Move tmp in moves)
			{
				int tmp_evaluate = minmax(Board(board, tmp), !player, depth + 1);
				if (tmp_evaluate >= evaluate)
				{
					evaluate = tmp_evaluate;
					bestMove = tmp;
				}
			}
			return evaluate;
		} //if (player)
		else
		{
			int evaluate = std::numeric_limits<int>::max();
			for each (Move tmp in moves)
			{
				int tmp_evaluate = minmax(Board(board, tmp), !player, depth + 1);
				if (tmp_evaluate <= evaluate)
				{
					evaluate = tmp_evaluate;
					bestMove = tmp;
				}
			}
			return evaluate;
		} //if (player) else
	} //if (depth == 0)
	else
	{
		if (player)
		{
			int evaluate = std::numeric_limits<int>::min();
			for each (Move tmp in moves)
				evaluate = std::max(evaluate, minmax(Board(board, tmp), !player, depth + 1));
			return evaluate;
		} //if (player)
		else
		{
			int evaluate = std::numeric_limits<int>::max();
			for each (Move tmp in moves)
				evaluate = std::min(evaluate, minmax(Board(board, tmp), !player, depth + 1));
			return evaluate;
		} //if (player) else
	} //if (depth == 0) else
} //int AI::minmax(Board board, bool player, int depth)

int AI::alphabeta(Board board, bool player, int depth, int alpha, int beta)
{
	numberNodes++;
	if (board.game_over() == 1) return -10000;
	if (board.game_over() == 0) return 10000;
	if (depth == max_depth) return board.evaluate();

	std::list<Move> moves;
	board.getJump(player, moves);
	if (moves.empty()) board.getMove(player, moves);

	switch (search_order)
	{
	case 1:
		moves.sort([](const Move& x, const Move& y){ return x.getValue() > y.getValue(); });
		break;
	case 2:
		moves.reverse();
		break;
	case 3:
		//moves.sort([](const Move& x, const Move& y){ return rand() % 2; });
		break;
	default:
		break;
	}

	if (depth == 0)
	{
		if (player)
		{
			for each (Move tmp in moves)
			{
				int tmp_evaluate = alphabeta(Board(board, tmp), !player, depth + 1, alpha, beta);
				if (tmp_evaluate >= alpha)
				{
					alpha = tmp_evaluate;
					bestMove = tmp;
				}
				if (alpha >= beta) return beta;
			}
			return alpha;
		} //if (player)
		else
		{
			for each (Move tmp in moves)
			{
				int tmp_evaluate = alphabeta(Board(board, tmp), !player, depth + 1, alpha, beta);
				if (tmp_evaluate <= beta)
				{
					beta = tmp_evaluate;
					bestMove = tmp;
				}
				if (beta <= alpha) return alpha;
			}
			return beta;
		} //if (player) else
	} //if (depth == 0)
	else
	{
		if (player)
		{
			for each (Move tmp in moves)
			{
				alpha = std::max(alpha, alphabeta(Board(board, tmp), !player, depth + 1, alpha, beta));
				if (alpha >= beta) return beta;
			}
			return alpha;
		} //if (player)
		else
		{
			for each (Move tmp in moves)
			{
				beta = std::min(beta, alphabeta(Board(board, tmp), !player, depth + 1, alpha, beta));
				if (beta <= alpha) return alpha;
			}
			return beta;
		} //if (player) else
	} //if (depth == 0) else
} //int AI::alphabeta(Board board, bool player, int depth, int alpha, int beta)