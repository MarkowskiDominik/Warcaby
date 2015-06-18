#include "Board.h"

Board::Board() : evaluateType() {}

Board::Board(int x) : evaluateType(x) {}

Board::Board(Board& source) : evaluateType(source.evaluateType)
{
	//copy board
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			(source(i, j)) ? fields[i][j] = new Figure(source(i, j)) : fields[i][j] = nullptr;
} //Board::Board(Board& source) : evaluateType(source.evaluateType)

Board::Board(Board& source, Move& move) : evaluateType(source.evaluateType)
{
	//copy board
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			(source(i, j)) ? fields[i][j] = new Figure(source(i, j)) : fields[i][j] = nullptr;

	//make move
	makeMove(move);
} //Board::Board(Board& source, Move& move) : evaluateType(source.evaluateType)

Board::~Board()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			delete fields[i][j];
}

void Board::create()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 1 && i != 3 && i != 4)
			{
				if (i < 3) fields[i][j] = new Figure(0, 0);
				if (i > 4) fields[i][j] = new Figure(1, 0);
			} //if ((i + j) % 2 == 1 && i != 3 && i != 4)
			else
				fields[i][j] = nullptr;
		} //for (int j = 0; j < 8; j++)
	} //for (int i = 0; i < 8; i++)
} //void createBoard()

void Board::show()
{
	cout << "    0  1  2  3  4  5  6  7\n";
	for (int i = 0; i < 8; i++)
	{
		cout << " " << i << " ";
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 1)
			{
				Figure* tmp = fields[i][j];
				if (tmp != nullptr)
				{
					if (tmp->type)
					{
						if (tmp->player) cout << " A ";
						else cout << " B ";
					} //if (tmp->type)
					else
					{
						if (tmp->player) cout << " a ";
						else cout << " b ";
					}
				} //if (tmp != nullptr)
				else cout << " ~ ";
			} //if ((i + j) % 2 == 1)
			else cout << "   ";
		} //for (int j = 0; j < 8; j++)
		cout << endl;
	} //for (int i = 0; i < 8; i++)
} //void showBoard()

int Board::evaluate()
{
	switch (evaluateType)
	{
	case 0: return evaluateNumber();
	case 1: return evaluateValue();
	case 2: return evaluateTactics();
	default: return evaluateValue();
	}
} //int Board::evaluate()

int Board::evaluateNumber()
{
	int aPoint = 0;
	int bPoint = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (fields[i][j] != nullptr)
			{
				if (fields[i][j]->player) aPoint++;
				else bPoint++;
			} //if (fields[i][j] != nullptr)
		} //for (int j = 0; j < 8; j++)
	} //for (int i = 0; i < 8; i++)

	return aPoint - bPoint;
} //int Board::evaluateNumber()

int Board::evaluateValue()
{
	int aPoint = 0;
	int bPoint = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (fields[i][j] != nullptr)
			{
				//pionek 1, damka 4
				if (fields[i][j]->player)
					(fields[i][j]->type) ? aPoint += 4 : aPoint++;
				else
					(fields[i][j]->type) ? bPoint += 4 : bPoint++;
			} //if (fields[i][j] != nullptr)
		} //for (int j = 0; j < 8; j++)
	} //for (int i = 0; i < 8; i++)

	return aPoint - bPoint;
} //int Board::evaluateValue()

int Board::evaluateTactics()
{
	int aPoint = 0;
	int bPoint = 0;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (fields[i][j] != nullptr)
			{
				if (fields[i][j]->player)
				{
					//pionek = (priorytet pola + odleg³oœæ + bezpieczeñstwo ruchu ) * 10;
					//damka = (priorytet pola + bezpieczeñstwo ruchu ) * 50
					(fields[i][j]->type) ? aPoint += (priorityD(i, j) + security(i, j)) * 50 : aPoint += (priorityP(i, j) + (7 - i) + security(i, j)) * 10;
				}
				else
				{
					//pionek = (priorytet pola + odleg³oœæ + bezpieczeñstwo ruchu ) * 10;
					//damka = (priorytet pola + bezpieczeñstwo ruchu ) * 10
					(fields[i][j]->type) ? bPoint += (priorityD(i, j) + security(i, j)) * 50 : bPoint += (priorityP(i, j) + i + security(i, j)) * 10;
				} //if (fields[i][j]->player)
			} //if (fields[i][j] != nullptr)
		} //for (int j = 0; j < 8; j++)
	} //for (int i = 0; i < 8; i++)

	return aPoint - bPoint;
} //int Board::evaluateTactics()

int Board::priorityP(int x, int y)
{
	if (x == 0 || x == 7 || y == 0 || y == 7) return 4;
	else
		if (x == 1 || x == 6 || y == 1 || y == 6) return 3;
		else
			if (x == 2 || x == 5 || y == 2 || y == 5) return 2;
			else
				return 1;
} //int Board::priorityP(int x, int y)

int Board::priorityD(int x, int y)
{
	if (x == 0 || x == 7 || y == 0 || y == 7) return 4;
	else
		if (x == 1 || x == 6 || y == 1 || y == 6) return 3;
		else return 2;
} //int Board::priorityD(int x, int y)

int Board::security(int x, int y)
{
	bool player = fields[x][y]->player;
	int value = 0;

	if (x == 0 || x == 7 || y == 0 || y == 7) return 4;
	else
	{
		if (fields[x - 1][y - 1] && fields[x - 1][y - 1]->player != player && !fields[x + 1][y + 1]) value--;
		if (fields[x - 1][y + 1] && fields[x - 1][y + 1]->player != player && !fields[x + 1][y - 1]) value--;
		if (fields[x + 1][y - 1] && fields[x + 1][y - 1]->player != player && !fields[x - 1][y + 1]) value--;
		if (fields[x + 1][y + 1] && fields[x + 1][y + 1]->player != player && !fields[x - 1][y - 1]) value--;
	}
	return value;
} //int Board::security(int x, int y)

int Board::game_over()
{
	if (aFigure == 0) return 1;
	if (bFigure == 0) return 0;
	return -1;
} //bool Board::game_over()

void Board::makeMove(Move& move)
{
	fields[move.getNewRow()][move.getNewColumn()] = fields[move.getOldRow()][move.getOldColumn()];
	fields[move.getOldRow()][move.getOldColumn()] = nullptr;

	//make attack
	if (move.getJump())
	{
		//delete fields[move.getAttackRow()][move.getAttackColumn()];
		(fields[move.getAttackRow()][move.getAttackColumn()]->player) ? aFigure-- : bFigure--;
		fields[move.getAttackRow()][move.getAttackColumn()] = nullptr;
	}

	promotion(move.getNewRow(), move.getNewColumn());
}

void Board::promotion(int row, int column)
{
	auto tmp = fields[row][column];
	if (tmp->player && !tmp->type && row == 0)
		tmp->type = 1;
	if (!tmp->player && !tmp->type && row == 7)
		tmp->type = 1;
}

void Board::getMove(bool player, std::list<Move>& moveList)
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			if (fields[row][column] != nullptr && fields[row][column]->player == player) //player figures
			{
				if (!fields[row][column]->type) //player pawn
				{
					if (player)
					{
						if (inBoard(row - 1, column - 1) && !fields[row - 1][column - 1])
							moveList.push_back(Move(row, column, row - 1, column - 1, evaluate()));

						if (inBoard(row - 1, column + 1) && !fields[row - 1][column + 1])
							moveList.push_back(Move(row, column, row - 1, column + 1, evaluate()));
					}
					else
					{
						if (inBoard(row + 1, column - 1) && !fields[row + 1][column - 1])
							moveList.push_back(Move(row, column, row + 1, column - 1, evaluate()));

						if (inBoard(row + 1, column + 1) && !fields[row + 1][column + 1])
							moveList.push_back(Move(row, column, row + 1, column + 1, evaluate()));
					}
				} //if (!fields[row][column]->type)
				else //player dame
				{
					int i;

					i = 1;
					while (inBoard(row - i, column - i) && !fields[row - i][column - i])
					{
						moveList.push_back(Move(row, column, row - i, column - i, evaluate()));
						i++;
					}

					i = 1;
					while (inBoard(row - i, column + i) && !fields[row - i][column + i])
					{
						moveList.push_back(Move(row, column, row - i, column + i, evaluate()));
						i++;
					}

					i = 1;
					while (inBoard(row + i, column - i) && !fields[row + i][column - i])
					{
						moveList.push_back(Move(row, column, row + i, column - i, evaluate()));
						i++;
					}

					i = 1;
					while (inBoard(row + i, column + i) && !fields[row + i][column + i])
					{
						moveList.push_back(Move(row, column, row + i, column + i, evaluate()));
						i++;
					}
				} //if (fields[row][column]->type) else
			} //if (fields[row][column] != nullptr && fields[row][column]->player == player)
		} //for (int column = 0; column < 8; column++)
	} //for (int row = 0; row < 8; row++)
} //std::list<Move>& Board::getMove(bool player)

void Board::getJump(bool player, std::list<Move>& jumpList)
{
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			if (fields[row][column] != nullptr && fields[row][column]->player == player) //player figures
			{
				if (!fields[row][column]->type) //player pawn
				{
					if (inBoard(row - 2, column - 2) && !fields[row - 2][column - 2] && fields[row - 1][column - 1] && fields[row - 1][column - 1]->player != player)
						jumpList.push_back(Move(row, column, row - 2, column - 2, evaluate(), row - 1, column - 1));

					if (inBoard(row - 2, column + 2) && !fields[row - 2][column + 2] && fields[row - 1][column + 1] && fields[row - 1][column + 1]->player != player)
						jumpList.push_back(Move(row, column, row - 2, column + 2, evaluate(), row - 1, column + 1));
					
					if (inBoard(row + 2, column - 2) && !fields[row + 2][column - 2] && fields[row + 1][column - 1] && fields[row + 1][column - 1]->player != player)
						jumpList.push_back(Move(row, column, row + 2, column - 2, evaluate(), row + 1, column - 1));

					if (inBoard(row + 2, column + 2) && !fields[row + 2][column + 2] && fields[row + 1][column + 1] && fields[row + 1][column + 1]->player != player)
						jumpList.push_back(Move(row, column, row + 2, column + 2, evaluate(), row + 1, column + 1));

				} //if (!fields[row][column]->type)
				else //player dame
				{
					int i, j;

					i = 1;
					while (inBoard(row - i, column - i) && !fields[row - i][column - i]) { i++; }
					if (inBoard(row - i, column - i) && fields[row - i][column - i]->player != player)
					{
						j = i + 1;
						while (inBoard(row - j, column - j) && !fields[row - j][column - j])
						{
							jumpList.push_back(Move(row, column, row - j, column - j, evaluate(), row - i, column - i));
							j++;
						}
					}

					i = 1;
					while (inBoard(row - i, column + i) && !fields[row - i][column + i]) { i++; }
					if (inBoard(row - i, column + i) && fields[row - i][column + i]->player != player)
					{
						j = i + 1;
						while (inBoard(row - j, column + j) && !fields[row - j][column + j])
						{
							jumpList.push_back(Move(row, column, row - j, column + j, evaluate(), row - i, column + i));
							j++;
						}
					}

					i = 1;
					while (inBoard(row + i, column - i) && !fields[row + i][column - i]) { i++; }
					if (inBoard(row + i, column - i) && fields[row + i][column - i]->player != player)
					{
						j = i + 1;
						while (inBoard(row + j, column - j) && !fields[row + j][column - j])
						{
							jumpList.push_back(Move(row, column, row + j, column - j, evaluate(), row + i, column - i));
							j++;
						}
					}

					i = 1;
					while (inBoard(row + i, column + i) && !fields[row + i][column + i]) { i++; }
					if (inBoard(row + i, column + i) && fields[row + i][column + i]->player != player)
					{
						j = i + 1;
						while (inBoard(row + j, column + j) && !fields[row + j][column + j])
						{
							jumpList.push_back(Move(row, column, row + j, column + j, evaluate(), row + i, column + i));
							j++;
						}
					}

				} //if (fields[row][column]->type) else
			} //if (fields[row][column] != nullptr && fields[row][column]->player == player)
		} //for (int column = 0; column < 8; column++)
	} //for (int row = 0; row < 8; row++)
} //std::list<Move>& Board::getMove(bool player)