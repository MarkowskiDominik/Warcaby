#include <cstdlib>
#include <iostream>
#include <Windows.h>

#include "Board.h"
#include "Move.h"
#include "AI.h"

using namespace std;

std::ostream& operator<< (std::ostream& os, const Move& move)
{
	return os << move.getOldRow() << " " << move.getOldColumn() << " -> " << move.getNewRow() << " " << move.getNewColumn() << " | "
		<< move.getAttackRow() << " " << move.getAttackColumn() << std::endl;
}

AI pcA, pcB;

int main()
{
	bool mode;
	cout << "Tryb gry - czlowiek vs PC(0) , PC vs PC(1)\n";
	cin >> mode;

	int evaluate;
	cout << "Ustawienia funkcji oceny\n"
		<< "0 - ilosc pionkow, 1 - wartosci pionkow, 2 - zlozona\n";
	cin >> evaluate;
	Board plansza(evaluate);

	int d, o;
	bool a;
	cout << "Ustawienia pc A\n"
		<< "glebokosc drzewa przeszukiwania, algorytm przeszukiwania (0 - minmax, 1 - alfabeta), kolejnosc wezlow (0 - domyslna, 1 - posortowana, 2 - odwrocona, 3 - random)\n";
	cin >> d; cin >> a; cin >> o;
	pcA = AI(d, a, o);

	if (mode)
	{
		cout << "Ustawienia pc B\n"
			<< "glebokosc drzewa przeszukiwania, algorytm przeszukiwania (0 - minmax, 1 - alfabeta), kolejnosc wezlow (0 - domyslna, 1 - posortowana, 2 - odwrocona, 3 - random)\n";
		cin >> d; cin >> a; cin >> o;
		pcB = AI(d, a, o);
	}
	system("PAUSE");

	Move ruch;
	bool player = true;
	/*
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if ((i + j) % 2 == 1)
				plansza(i, j) = nullptr;
	plansza(0, 1) = new Figure(0, 0);
	plansza(0, 3) = new Figure(0, 0);
	plansza(0, 5) = new Figure(1, 1);
	plansza(0, 1) = new Figure(0, 0);
	plansza(0, 7) = new Figure(0, 0);
	plansza(1, 0) = new Figure(0, 0);
	plansza(2, 7) = new Figure(0, 0);
	plansza(3, 2) = new Figure(1, 0);
	plansza(5, 0) = new Figure(1, 0);
	plansza(5, 2) = new Figure(0, 0);
	plansza(5, 6) = new Figure(1, 0);
	plansza(6, 7) = new Figure(1, 0);
	plansza(7, 0) = new Figure(1, 0);
	plansza(7, 4) = new Figure(0, 1);
	plansza(7, 6) = new Figure(1, 0);
	*/
	plansza.create();
	plansza.show();

	pcA.search(plansza, 0);
	cout << pcA.getNumberNodes() << "\t";
	pcB.search(plansza, 0);
	cout << pcB.getNumberNodes();
	system("PAUSE");

	while (plansza.game_over() < 0)
	{
		if (player) //gracz 1
		{
			if (mode) //komputer
			{
				//Sleep(500);
				ruch = pcA.search(plansza, 1);
				cout << "GRACZ A:   " << ruch;
				plansza.makeMove(ruch);
				plansza.show();
				//cout << plansza.evaluate() << endl;
				//system("PAUSE");
				cout << endl;
			}
			else //czlowiek
			{
				std::list<Move> moves;
				plansza.getJump(player, moves);
				if (moves.empty()) plansza.getMove(player, moves);

				bool getMove = true;
				int a, b, x, y;
				do
				{
					cout << "podaj poprawny ruch\n";
					cin >> a; cin >> b; cin >> x; cin >> y;
					ruch = Move(a, b, x, y, 0);
					for (auto move : moves)
					{
						if (move == ruch)
						{
							ruch = move;
							getMove = false;
						}
					}
				} while (getMove);

				plansza.makeMove(ruch);
				cout << endl;
			}
		}
		else //gracz 0
		{
			//Sleep(500);
			ruch = pcB.search(plansza, 0);
			cout << "GRACZ B:   " << ruch;
			plansza.makeMove(ruch);
			plansza.show();
			//cout << plansza.evaluate() << endl;
			//system("PAUSE");
			cout << endl;
		}
		player = !player;
	}
	cout << "przegral gracz: " << plansza.game_over() << endl;

	system("PAUSE");
	return 0;
}